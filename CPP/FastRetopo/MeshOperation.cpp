#include "MeshOperation.h"

MStatus MeshOperations::LaplacianSmooth(Graph* graph)
{   
    MStatus status;

    MGlobal::displayInfo("Processing Laplacian Smooth...");
    auto start = high_resolution_clock::now();

    for (int point_idx = 0; point_idx < graph->vertices.size(); point_idx++) {

        MPoint result_pos = { 0, 0, 0 };

        MIntArray neighbours = graph->neighborhood_relations[point_idx];
        unsigned int neighbours_nb = neighbours.length();
        for (int neighbour_idx = 0; neighbour_idx < neighbours_nb; neighbour_idx++)
        {
            int neighbour_id = neighbours[neighbour_idx];
            MPoint neighbour_position = graph->vertices[neighbour_id].position;

            result_pos[0] += neighbour_position[0];
            result_pos[1] += neighbour_position[1];
            result_pos[2] += neighbour_position[2];
        }

        if (neighbours_nb) {
            result_pos[0] /= neighbours.length();
            result_pos[1] /= neighbours.length();
            result_pos[2] /= neighbours.length();
        }
        
        graph->vertices[point_idx].position = result_pos;

    }

    /* Calc duration */
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    MString duration_info = "Laplacian Smooth : ";
    duration_info += (float)duration.count() / 1000;
    duration_info += " ms.";
    MGlobal::displayInfo(duration_info);

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

MStatus MeshOperations::ComputeVerticesGraph(Mesh mesh, Graph* graph)
{
    MStatus status;

    MFnMesh fnMesh(mesh.dagPath);

    MGlobal::displayInfo("Processing Vertices Graph...");

    MItMeshVertex vert_it(mesh.dagPath, mesh.component, &status);
    if (!status)
    {
        MGlobal::displayError("Failed to get Vertex iteration: " + status.errorString());
        return status;
    }

    for (; !vert_it.isDone(); vert_it.next()) {

        Vertex curr_vertex;
        curr_vertex.position = vert_it.position(MSpace::kWorld);
        CHECK_STATUS(vert_it.getNormal(curr_vertex.normal, MSpace::kWorld), "Getting vertex normal");

        graph->vertices.push_back(curr_vertex);

        MIntArray neighbours;
        CHECK_STATUS(vert_it.getConnectedVertices(neighbours), "Getting connected vertices.");

        graph->neighborhood_relations.push_back(neighbours);
    }

    return MS::kSuccess;
}

MStatus MeshOperations::ApplyGraphToMesh(Graph graph, Mesh mesh)
{

    MFnMesh fnMesh(mesh.dagPath);
    MPointArray points;
    for (int i = 0; i < graph.vertices.size(); i++) {
        points.append(graph.vertices[i].position);
    }

    CHECK_STATUS(fnMesh.setPoints(points), "Setting points positions.");

    return MS::kSuccess;
}
