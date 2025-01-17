#include "MeshOperation.h"

MStatus MeshOperations::LaplacianSmooth(Mesh mesh)
{   
    MStatus status;

    MFnMesh fnMesh(mesh.dagPath);

    MGlobal::displayInfo("Processing Laplacian Smooth...");
    
    MItMeshVertex vert_it(mesh.dagPath, mesh.component, &status);
    if (!status)
    {
        MGlobal::displayError("Failed to get Vertex iteration: " + status.errorString());
        return status;
    }

    for (; !vert_it.isDone(); vert_it.next()) {

        double result_pos[3] = { 0, 0, 0 };
        MIntArray neighbours;
        CHECK_STATUS(vert_it.getConnectedVertices(neighbours), "Getting connected vertices.");
        unsigned int neighbours_nb = neighbours.length();
        for (int neighbour_idx = 0; neighbour_idx < neighbours_nb; neighbour_idx++)
        {
            MPoint neighbour_position;
            CHECK_STATUS(fnMesh.getPoint(neighbours[neighbour_idx], neighbour_position, MSpace::kWorld), "Getting point position.");

            result_pos[0] += neighbour_position[0];
            result_pos[1] += neighbour_position[1];
            result_pos[2] += neighbour_position[2];
        }

        if (neighbours_nb) {
            result_pos[0] /= neighbours.length();
            result_pos[1] /= neighbours.length();
            result_pos[2] /= neighbours.length();
        }
        
        vert_it.setPosition(result_pos, MSpace::kWorld);

    }

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