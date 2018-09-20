/*
 * Mesh.h
 *
 *  Created on: Aug 21, 2018
 *      Author: saman
 */

#ifndef MESH_H_
#define MESH_H_

#include <boost/multi_array.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <iostream>
#include <string>
#include <netcdf>

#include "Element.h"
#include "Nodesets.h"

using namespace std;
//using namespace boost::numeric::ublas;


namespace FSDE {

class Mesh {

public:
	Mesh();

	/** Reading the mesh from netcdf compatible files **/
	Mesh(string fileName);

	virtual ~Mesh();

	/** Get the coordinates of nodes **/
	boost::multi_array<double, 2> GetNodalCoordinates();

	/** Reads the element connectivity information **/
	boost::multi_array<int, 2> GetConnectivity();

	int GetNumDim() const;

	int GetNumElements() const;

	int GetNumNodes() const;

	int GetNumNodesets() const;

	int GetNumNodesPerElement() const;

	/** Returns set of nodes **/
	vector<Node> GetNodes();

	/** Returns set of element **/
	vector<Element> GetElements();

	/** Returns set of nodesets for boundary conditions **/
	vector<Nodesets> GetNodeSets();

	vector<Edge> GetEdges(); // Not implemented yet!

	string GetElementType();

	void PrintMeshInfo();

protected:

	/** Creating edges of for the element **/
	vector<Edge> CreateEdges(Element, vector<int>);

	int _num_dim;
	int _num_elem;
	int _num_nodes;
	int _num_nodes_per_elem;
	int _num_nodesets;

	int _num_edges_per_elem;

	string _str_elem_type;

private:


	netCDF::NcFile *dataFile;

	vector<Node> _node_vector;
	vector<Element> _element_vector;
	vector<Nodesets> _nodesets_vector;
	vector<Edge> _edge_vector;

//	boost::numeric::ublas::matrix<int> adjacencyMatrix;


};

} /* namespace FSDE2D */

#endif /* MESH_H_ */
