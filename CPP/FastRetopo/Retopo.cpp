#include "Retopo.h"


MStatus Retopo::RetopoMeshes()
{
    MStatus status;

    MSelectionList selection;
    CHECK_STATUS(GetSelection(&selection), "Error getting selection.");

    Mesh selected_mesh;
    CHECK_STATUS(GetMeshFromSelection(&selected_mesh, selection, 0), "Error getting selected mesh.");
    MGlobal::displayInfo(selected_mesh.dagPath.fullPathName());

    unsigned int vertices_nb;
    CHECK_STATUS(MeshOperations::VerticesCount(selected_mesh, &vertices_nb), "Error getting vertices number.");
    MGlobal::displayInfo(MString("Selected mesh contained : ") + vertices_nb + " vertices.");

    CHECK_STATUS(MeshOperations::LaplacianSmooth(selected_mesh), "Error laplacian smooth.");

    return MS::kSuccess;

}

MStatus Retopo::GetSelection(MSelectionList* selection)
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