#pragma once

#include <maya/MPxCommand.h>
#include "Retopo.h"

class RetopoCommand : public MPxCommand
{

public: 
	static void* creator();

	MStatus doIt(const MArgList& args) override;

};