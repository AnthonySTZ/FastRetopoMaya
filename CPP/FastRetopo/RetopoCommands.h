#pragma once

#include <maya/MPxCommand.h>

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>
#include <maya/MString.h>
#include <maya/MObject.h>

class RetopoCommand : public MPxCommand
{

public: 
	static void* creator();

	MStatus doIt(const MArgList& args) override;

};