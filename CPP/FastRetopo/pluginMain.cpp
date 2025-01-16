#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include "RetopoCommands.h"

const MString RetopoCmd = "fastRetopo";

MStatus initializePlugin(MObject obj)
{
	const char* pluginVendor = "ASTZ";
	const char* pluginVersion = "0.1";

	MFnPlugin fnPlugin(obj, pluginVendor, pluginVersion);
	MGlobal::displayInfo("Plugin has been initialized!");

	MStatus status = fnPlugin.registerCommand(RetopoCmd, RetopoCommand::creator);

	return (MS::kSuccess);
}

MStatus uninitializePlugin(MObject obj)
{
	MGlobal::displayInfo("Plugin has been uninitialize!");

	return (MS::kSuccess);
}