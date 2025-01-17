#include "RetopoCommands.h"


void* RetopoCommand::creator()
{
    return new RetopoCommand;
}

MStatus RetopoCommand::doIt(const MArgList& args){

    MStatus status = Retopo::RetopoMeshes();
    return status;
}

