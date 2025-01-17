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

#include <chrono>
using namespace std::chrono;

#include <vector>

#include "macros.h"

struct Mesh {
	MDagPath dagPath;
	MObject component;
};

struct Vertex {
	double position[3];
	double normal[3];
};

struct Graph{

	std::vector<Vertex> vertices;
	std::vector<std::vector<Vertex>> neighborhood_relations;

};

class MeshOperations
{
public:
	static MStatus LaplacianSmooth(Mesh mesh);
	static MStatus VerticesCount(Mesh mesh, unsigned int* vertices_count);
};