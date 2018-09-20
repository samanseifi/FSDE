//============================================================================
// Name        : FSDE2D.cpp
// Author      : Saman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// HAS TO BE COMPILED WITH -lnetcdf_c++4 not -lnetcdf look bookmarked page in firefox!

#include "Mesh.h"

using namespace FSDE;

void TestMesh(Mesh msh);
void FormStiffness(Eigen::MatrixXd &K);
void ConstructStifness(Element);

int main(){




 	Mesh msh1("geom2.g");

	vector<Node> nodes = msh1.GetNodes();
	cout << "Number of Nodes= " << nodes.size() << endl;
	vector<double> coords12 = nodes[12].GetCoordinates();
	cout << "Node number 12 has the coordinates= " << coords12[0] << " , " << coords12[1] << endl;
	vector<Element> elem = msh1.GetElements();
	cout << msh1.GetElementType();

	vector<Node> elem12 = elem[12].GetNodeVector();
	cout << "Node ID of the second node in element 12 = " << elem12[1].GetID() << endl;
	cout << "Number of elements= " << msh1.GetNumElements() << endl;
	cout << "The 4th node of nodeset 2 has the node number = " << msh1.GetNodeSets()[1].GetNodes()[3].GetID() << endl;

//	cout << "Edge vector of element 12= " << elem[12].GetEdgeVector()[0] << " " << elem[12].GetEdgeVector()[1] <<
//			" " << elem[12].GetEdgeVector()[2] << " " << elem[12].GetEdgeVector()[3] << endl;


	vector<Edge> alledges = msh1.GetEdges();
	cout << "Total number of edges = " << alledges.size() << endl;

	cout << "---------------------------\n";

	return 0;
}



void FormStiffness(Eigen::MatrixXd &K) {

}

void ConstructStifness (Element el) {

}


void TestMesh(Mesh msh1) {



}
