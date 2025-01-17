#include "MeshOperation.h"

MStatus MeshOperations::LaplacianSmooth(Mesh mesh)
{
    MGlobal::displayInfo("Laplacian Smooth");

    return MS::kSuccess;
}

MStatus MeshOperations::VerticesCount(Mesh mesh, unsigned int* vertices_count)
{
    MStatus status;
    MItMeshVertex vert_it(mesh.dagPath, mesh.component, &status);
    if (!status)
    {
        MGlobal::displayError("Failed to get Vertex iteration: " + status.errorString());
        return status;
    }

    *vertices_count = vert_it.count();

    return MS::kSuccess;
}