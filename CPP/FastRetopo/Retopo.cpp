#include "Retopo.h"

MStatus Retopo::RetopoMeshes()
{

    MSelectionList selection;
    MGlobal::getActiveSelectionList(selection);

    if (selection.isEmpty())
    {
        MGlobal::displayWarning("No objects selected!");
        return MS::kFailure;
    }

    MDagPath item;
    MObject component;
    MStatus status = selection.getDagPath(0, item, component); /* Get only the first selected objects TODO: Loop over all selected objects */
    if (!status)
    {
        MGlobal::displayError("Failed to get DAG path: " + status.errorString());
        return status;
    }

    MGlobal::displayInfo(item.fullPathName());

    MItMeshVertex vert_it(item, component, &status);
    if (!status)
    {
        MGlobal::displayError("Failed to get Vertex iteration: " + status.errorString());
        return status;
    }

    MString vert_count_display;
    int vert_nb = vert_it.count();

    vert_count_display += vert_nb;
    MGlobal::displayInfo(vert_count_display);

    return MS::kSuccess;

}
