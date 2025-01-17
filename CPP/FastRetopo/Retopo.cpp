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

    unsigned int vertices_nb;
    CHECK_STATUS(MeshOperations::VerticesCount(selected_mesh, &vertices_nb));
    MGlobal::displayInfo(MString("Selected mesh contained : ") + vertices_nb + " vertices.");

    CHECK_STATUS(MeshOperations::LaplacianSmooth(selected_mesh));

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