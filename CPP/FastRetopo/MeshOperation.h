#pragma once

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>
#include <maya/MString.h>
#include <maya/MObject.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>


#include <vector>
#include <math.h>

#include "macros.h"

struct Mesh {
	MDagPath dagPath;
	MObject component;
};

struct Vertex {
	MPoint position;
	MVector normal;
};

struct Graph{

	std::vector<Vertex> vertices;
	std::vector<MIntArray> neighborhood_relations;

};


struct OrientationField {

	int so;
	std::vector<MVector> representative_vectors;

};

class MeshOperations
{
public:
	static MStatus VerticesCount(Mesh mesh, unsigned int* vertices_count);
	static MStatus ComputeVerticesGraph(Mesh mesh, Graph* graph);
	static MStatus ApplyGraphToMesh(Graph graph, Mesh mesh);
	static MStatus ComputeOrientationField(Graph graph, OrientationField* orientation_field, int max_iterations);
	static MStatus InitializeOrientationField(Graph graph, OrientationField* orientation_field);

private:
	static int* get_pair_of_rotations(int so, MVector oi, MVector oj, MVector ni, MVector nj);
	static MVector Rso(int so, MVector o, MVector n, int k);
	static double angle_between_normalized(MVector v1, MVector v2);
	static MVector project_on_plane(MVector v1, MVector plane_normal);
};