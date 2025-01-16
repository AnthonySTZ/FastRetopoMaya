#include "RetopoCommands.h"

void* RetopoCommand::creator()
{
    return new RetopoCommand;
}

MStatus RetopoCommand::doIt(const MArgList& args)
{
    const MStatus status = MGlobal::executeCommand("polyCube");
    if (!status) {
        MGlobal::displayError("Failed to create ball: " + status.errorString());
    }
    return MStatus();
}

