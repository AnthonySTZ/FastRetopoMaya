#pragma once

#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>

class RetopoCommand : public MPxCommand
{

public: 
	static void* creator();

	MStatus doIt(const MArgList& args) override;

};