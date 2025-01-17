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

#include <chrono>
using namespace std::chrono;

#include <vector>

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

class MeshOperations
{
public:
	static MStatus LaplacianSmooth(Graph* graph);
	static MStatus VerticesCount(Mesh mesh, unsigned int* vertices_count);
	static MStatus ComputeVerticesGraph(Mesh mesh, Graph* graph);
	static MStatus ApplyGraphToMesh(Graph graph, Mesh mesh);
};