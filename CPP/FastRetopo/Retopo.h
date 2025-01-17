#pragma once

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>
#include <maya/MString.h>
#include <maya/MObject.h>

#include <vector>

struct Mesh {
	MDagPath dagPath;
	MObject component;
};

class Retopo
{

public: 
	static MStatus RetopoMeshes();

private:

	static MStatus GetSelectedMesh(MSelectionList* selection);
	static MStatus GetMeshFromSelection(Mesh* mesh, MSelectionList selection, unsigned int index);
	static MStatus VerticesCount(Mesh mesh, unsigned int* vertices_count);
};