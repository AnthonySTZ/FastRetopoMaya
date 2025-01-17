#include "Retopo.h"

#define CHECK_STATUS(status)            \
{                                       \
    if (!status) return MS::kFailure;   \
}                                       \

MStatus Retopo::RetopoMeshes()
{
    MStatus status;

    MSelectionList selection;
    CHECK_STATUS(GetSelectedMesh(&selection));

    Mesh selected_mesh;
    CHECK_STATUS(GetMeshFromSelection(&selected_mesh, selection, 0));


    MGlobal::displayInfo(selected_mesh.dagPath.fullPathName());

    MItMeshVertex vert_it(selected_mesh.dagPath, selected_mesh.component, &status);
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

MStatus Retopo::GetSelectedMesh(MSelectionList* selection)
{
    MGlobal::getActiveSelectionList(*selection);

    if (selection->isEmpty())
    {
        MGlobal::displayWarning("No objects selected!");
        return MS::kFailure;
    }

    return MS::kSuccess;
}

MStatus Retopo::GetMeshFromSelection(Mesh *mesh, MSelectionList selection, unsigned int index)
{
    MDagPath item;
    MObject component;
    MStatus status = selection.getDagPath(index, item, component);
    if (!status)
    {
        MGlobal::displayError("Failed to get DAG path: " + status.errorString());
        return status;
    }

    mesh->dagPath = item;
    mesh->component = component;

    return MS::kSuccess;
}
