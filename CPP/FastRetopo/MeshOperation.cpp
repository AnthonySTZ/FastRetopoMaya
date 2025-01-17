#include "MeshOperation.h"


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

MStatus MeshOperations::ComputeOrientationField(Graph graph, OrientationField* orientation_field)
{



    return MS::kSuccess;
}
