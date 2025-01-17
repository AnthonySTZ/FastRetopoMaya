#pragma once

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>
#include <maya/MString.h>
#include <maya/MObject.h>

struct Mesh {
	MDagPath dagPath;
	MObject component;
};

class MeshOperations
{
public:
	static MStatus LaplacianSmooth(Mesh mesh);
	static MStatus VerticesCount(Mesh mesh, unsigned int* vertices_count);
};