#include "RetopoCommands.h"


void* RetopoCommand::creator()
{
    return new RetopoCommand;
}

MStatus RetopoCommand::doIt(const MArgList& args){

    MSelectionList selection;
    MGlobal::getActiveSelectionList(selection);

    if (selection.isEmpty())
    {
        MGlobal::displayWarning("No objects selected!");
        return MS::kFailure;
    }

    MItSelectionList iter(selection);


    for (; !iter.isDone(); iter.next()) // For each selected object
    {
        MObject component;
        MDagPath item;
        MStatus status = iter.getDagPath(item, component);
        if (!status)
        {
            MGlobal::displayError("Failed to get DAG path!");
            return status;
        }

        MGlobal::displayInfo(item.fullPathName());
    }

    return MS::kSuccess;
}

