/*
 * Mesh.cpp
 *
 *  Created on: Aug 21, 2018
 *  Uploaded on: Sep 19, 2018
 *      Author: Saman Seifi
 */

#include <Mesh.h>

#include <algorithm>
#include <set>

namespace FSDE {

Mesh::Mesh() {
	dataFile = NULL;
	this->_num_dim = 0;
	this->_num_elem = 0;
	this->_num_nodes = 0;
	this->_num_nodes_per_elem = 0;
	this->_num_nodesets = 0;
	this->_num_edges_per_elem = 0;
}

Mesh::Mesh(string fileName){
	try {
		dataFile = new netCDF::NcFile(fileName, netCDF::NcFile::read);
		if (dataFile->isNull()) {
			throw "ERR: Unable to open file " + fileName + "\n";
		}

		// Initialization of geometrical dimensions
		this->_num_dim 	= dataFile->getDim("num_dim").getSize();
		this->_num_elem = dataFile->getDim("num_elem").getSize();
		this->_num_nodes = dataFile->getDim("num_nodes").getSize();
		this->_num_nodesets = dataFile->getDim("num_node_sets").getSize();
		this->_num_nodes_per_elem = dataFile->getDim("num_nod_per_el1").getSize();

		this->_num_edges_per_elem = _num_nodes_per_elem; // # of nodes = # edges per element

		// Initialization of geometrical variables with their proper dimensions
		_node_vector.reserve(_num_nodes);
		_element_vector.reserve(_num_elem);
		_nodesets_vector.reserve(_num_nodesets);

		// Fill the vectors with the mesh informations
		_node_vector = GetNodes();
		_element_vector = GetElements();
		_nodesets_vector = GetNodeSets();

//		PrintMeshInfo();

	} catch (const char* msg) {
		cerr << msg << endl;
	}
}

Mesh::~Mesh() {
	delete dataFile;
}

// Creating the array of nodal coordinates with size: (num dimensions) x (num nodes)
boost::multi_array<double, 2> Mesh::GetNodalCoordinates(){

	boost::multi_array<double, 2> array(boost::extents[_num_dim][_num_nodes]);

	try {
		netCDF::NcVar nodeData = dataFile->getVar("coord");
		if (nodeData.isNull()){
			cerr << "ERR: Can't read the nodal data.\n";
		}
		nodeData.getVar(array.data());

	} catch (const char* msg) {
		cerr << msg << endl;
	}
	return array;
}

// Creating the array of connectivity matrix with size: (num nodes per element) x (num elements)
boost::multi_array<int, 2> Mesh::GetConnectivity(){

	boost::multi_array<int, 2> connectivityArray(boost::extents[_num_elem][_num_nodes_per_elem]);

	try {
		netCDF::NcVar connectivityData = dataFile->getVar("connect1");

		// Identifying the element type (only quad and hex element for now)
		connectivityData.getAtt("elem_type").getValues(_str_elem_type);

		if (_str_elem_type.compare("SHELL4") || _str_elem_type.compare("QUAD4")) {
			cout << "2D 4-noded quad element detected.\n";
			assert(unsigned(_num_dim) == 2);
		} else if (_str_elem_type.compare("HEX8")) {
			cout << "3D 8-noded Hexagonal element detected.\n";
			assert(unsigned(_num_dim) == 3);
		} else {
			cerr << "ERR: Element type " << _str_elem_type << " is not implemented yet!\n";
		}

		if (connectivityData.isNull()) {
			cerr << "ERR: Can't read the connectivity data.\n";
		}
		connectivityData.getVar(connectivityArray.data());

	} catch (const char* msg) {
		cerr << msg << endl;
	}
	return connectivityArray;
}

// Number of Mesh dimensions
int Mesh::GetNumDim() const {
	return _num_dim;
}

// Number of elements
int Mesh::GetNumElements() const {
	return _num_elem;
}

// Number of nodes
int Mesh::GetNumNodes() const {
	return _num_nodes;
}

// Number of nodesets
int Mesh::GetNumNodesets() const {
	return _num_nodesets;
}

// Number of nodes per element (for now = 4)
int Mesh::GetNumNodesPerElement() const {
	return _num_nodes_per_elem;
}

vector<Node> Mesh::GetNodes(){
    // Create the vector of nodes.
	boost::multi_array<double, 2> nodalArray = GetNodalCoordinates();

	// Confirmation if the size of the nodal matrix is correct.
	assert(nodalArray.shape()[0] == unsigned(_num_dim));
	assert(nodalArray.shape()[1] == unsigned(_num_nodes));

    for (int i = 0; i < _num_nodes; i++) {
		if (_num_dim == 2) {
			_node_vector.push_back(Node(i + 1, nodalArray[0][i], nodalArray[1][i]));
		} else if (_num_dim == 3) {
			_node_vector.push_back(Node(i + 1, nodalArray[0][i],
											   nodalArray[1][i],
										   	   nodalArray[2][i]));
		} else if (_num_dim == 1) {
			cout << "ERR: Does not support DIM=" << _num_dim << endl;
		} else {
			cout << "ERR: Wrong dimension DIM=" << _num_dim << " !\n";
		}

    }
	return _node_vector;
}

vector<Element> Mesh::GetElements() {
	// Create the vector of elements
	boost::multi_array<int, 2> connectVector = GetConnectivity();

	// Confirmation if the size of the connectivity is correct
	assert(connectVector.shape()[0] == unsigned(_num_elem)); // for now for 2D problems
	assert(connectVector.shape()[1] == unsigned(_num_nodes_per_elem));

	vector<Node> elem_nodes(_num_nodes_per_elem); // this works for n-noded element!
	for (int i = 0; i < _num_elem; i++) {
		for (int j = 0; j < _num_nodes_per_elem; j++) {
			elem_nodes.push_back(_node_vector[connectVector[i][j] - 1]);
		}

		Element newElem = Element(i+1, elem_nodes);

		// Create the element edges
		vector<Edge> VectorOfEdges;
		if (_str_elem_type.compare("SHELL4")) {
			newElem.SetElemType(_str_elem_type);
			VectorOfEdges.reserve(4);
			VectorOfEdges = CreateEdges(newElem, { connectVector[i].begin(), connectVector[i].end() });
		} else if (_str_elem_type.compare("HEX8")) {
			newElem.SetElemType(_str_elem_type);
			VectorOfEdges.reserve(8);
			VectorOfEdges = CreateEdges(newElem, { connectVector[i].begin(), connectVector[i].end() });

		} else {
			cout << "ERR: Element implmentation error!\n";
		}

		// Setting the edges to the element
		newElem.SetEdgeVector(VectorOfEdges);

		// Pushing the new element to the vector of elements
		_element_vector.push_back(newElem);

	}
	return _element_vector;
}

vector<Nodesets> Mesh::GetNodeSets() {
	for (int n = 0; n < _num_nodesets; n++){
		string strNodeSetName = "node_ns" + std::to_string(n+1);
		netCDF::NcVar nsData = dataFile->getVar(strNodeSetName);
		int nsSize = nsData.getDim(0).getSize();
		int nsArray[nsSize];
		nsData.getVar(nsArray);

		vector<Node> nsVec;
		for (int i = 0; i < nsSize; i++) {
			nsVec.push_back(_node_vector[nsArray[i] - 1]);
		}
		_nodesets_vector.push_back(Nodesets(nsVec, n + 1));
    }
	return _nodesets_vector;
}

vector<Edge> Mesh::GetEdges() {
	// TODO: incorrect implementation duplicated edges are not removed :(
	boost::multi_array<int, 2> connectVector = GetConnectivity();
	for (unsigned int i = 0; i < connectVector.shape()[0]; i++ ) {
		Edge edge1(pair <Node, Node> (_node_vector[connectVector[i][0]], _node_vector[connectVector[i][1]]));
	 	Edge edge2(pair <Node, Node> (_node_vector[connectVector[i][1]], _node_vector[connectVector[i][2]]));
	 	Edge edge3(pair <Node, Node> (_node_vector[connectVector[i][2]], _node_vector[connectVector[i][3]]));
	 	Edge edge4(pair <Node, Node> (_node_vector[connectVector[i][3]], _node_vector[connectVector[i][0]]));

	 	_element_vector[i].SetEdgeVector({ edge1, edge2, edge3, edge4 });

		_edge_vector.push_back(edge1);
		_edge_vector.push_back(edge2);
		_edge_vector.push_back(edge3);
		_edge_vector.push_back(edge4);
	}

	return _edge_vector;

}

string Mesh::GetElementType() {
	return _str_elem_type;
}

void Mesh::PrintMeshInfo() {

	cout << "MESH INFO:\n";
	cout << endl;
	cout << "Dimension (_num_dim).........................." << this->_num_dim << endl;
	cout << "Number of elements (_num_elem)................" << this->_num_elem << endl;
	cout << "Element type (_elem_type)....................." << this->_str_elem_type << endl;
	cout << "Number of nodesets (_num_nodesets)............" << this->_num_nodesets << endl;

}

vector<Edge> Mesh::CreateEdges(Element elem, vector<int> connectVector) {

	vector<Edge> edges(elem.GetNodeVector().size());
	if (connectVector.size() == 4) {
		Edge edge1(pair <Node, Node> (_node_vector[connectVector[0] - 1], _node_vector[connectVector[1] - 1]));
	 	Edge edge2(pair <Node, Node> (_node_vector[connectVector[1] - 1], _node_vector[connectVector[2] - 1]));
	 	Edge edge3(pair <Node, Node> (_node_vector[connectVector[2] - 1], _node_vector[connectVector[3] - 1]));
	 	Edge edge4(pair <Node, Node> (_node_vector[connectVector[3] - 1], _node_vector[connectVector[0] - 1]));
	 	edges = { edge1, edge2, edge3, edge4 };

	} else if (connectVector.size() == 8) {
		// Top surface edges
		Edge edge1(pair <Node, Node> (_node_vector[connectVector[0] - 1], _node_vector[connectVector[1] - 1]));
	 	Edge edge2(pair <Node, Node> (_node_vector[connectVector[1] - 1], _node_vector[connectVector[2] - 1]));
	 	Edge edge3(pair <Node, Node> (_node_vector[connectVector[2] - 1], _node_vector[connectVector[3] - 1]));
	 	Edge edge4(pair <Node, Node> (_node_vector[connectVector[3] - 1], _node_vector[connectVector[0] - 1]));

	 	// Bottom surface edges
	 	Edge edge5(pair <Node, Node> (_node_vector[connectVector[4] - 1], _node_vector[connectVector[5] - 1]));
	 	Edge edge6(pair <Node, Node> (_node_vector[connectVector[5] - 1], _node_vector[connectVector[6] - 1]));
	 	Edge edge7(pair <Node, Node> (_node_vector[connectVector[6] - 1], _node_vector[connectVector[7] - 1]));
	 	Edge edge8(pair <Node, Node> (_node_vector[connectVector[7] - 1], _node_vector[connectVector[4] - 1]));

	 	// Connecting edges
	 	Edge edge9(pair <Node, Node> (_node_vector[connectVector[0] - 1], _node_vector[connectVector[4] - 1]));
	 	Edge edge10(pair <Node, Node> (_node_vector[connectVector[1] - 1], _node_vector[connectVector[5] - 1]));
	 	Edge edge11(pair <Node, Node> (_node_vector[connectVector[2] - 1], _node_vector[connectVector[6] - 1]));
	 	Edge edge12(pair <Node, Node> (_node_vector[connectVector[3] - 1], _node_vector[connectVector[7] - 1]));
	 	edges = { edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12 };

	} else {
		cout << "ERR: Not implemented yet!\n";
	}

	return edges;
}



/* 	4-noded quad element       		 8-noded hex element
       (code name: SHELL4, QUAD4) 	           (code name: HEX8)

                                             4             3
2             1                               O-------------O
O-------------O                              /|            /|
|             |                             / |           / |
|             |                            /  |          /  |
|             |                           /   |         /   |
|             |                        1 /    |      2 /    |
|             |                         O----8|-------O    7|
|             |                         |     O-------|-----O
O-------------O                         |    /        |    /
3	      4                         |   /         |   /
                                        |  /          |  /
                                        | /           | /
                                       5|/           6|/
                                        O-------------O
 *
 */

} /* namespace FSDE */
