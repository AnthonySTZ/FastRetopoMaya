#include "MeshOperation.h"
# define M_PIl          3.141592653589793238462643383279502884L


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

    MGlobal::displayInfo("Applying Graph to Mesh...");

    MFnMesh fnMesh(mesh.dagPath);
    MPointArray points;
    for (int i = 0; i < graph.vertices.size(); i++) {
        points.append(graph.vertices[i].position);
    }

    CHECK_STATUS(fnMesh.setPoints(points), "Setting points positions.");

    return MS::kSuccess;
}

MStatus MeshOperations::ComputeOrientationField(Graph graph, OrientationField* orientation_field, int max_iterations)
{

    MGlobal::displayInfo("Processing Orientation Field...");

    int so = orientation_field->so;

    for (int iteration = 0; iteration < max_iterations; iteration++) {

        for (int vertex_idx = 0; vertex_idx < graph.vertices.size(); vertex_idx++) {
            MVector oi = orientation_field->representative_vectors[vertex_idx];
            MVector oi_prime = { 0, 0, 0 };
            MVector ni = graph.vertices[vertex_idx].normal;

            for (unsigned int neighbour_idx = 0; neighbour_idx < graph.neighborhood_relations[vertex_idx].length(); neighbour_idx++) {

                MVector oj = orientation_field->representative_vectors[neighbour_idx];
                MVector nj = graph.vertices[neighbour_idx].normal;

                int* best_rotations = get_pair_of_rotations(so, oi, oj, ni, nj);
                int k_ij = best_rotations[0];

                oi_prime += Rso(so, oj, ni, k_ij);
                oi = oi_prime.normal();

            }

            orientation_field->representative_vectors[vertex_idx] = oi;

        }

    }

    MGlobal::displayInfo("Orientation Field Processed...");

    return MS::kSuccess;
}

MStatus MeshOperations::InitializeOrientationField(Graph graph, OrientationField* orientation_field)
{
    MGlobal::displayInfo("Initializing Orientation Field...");

    for (int vertex_idx = 0; vertex_idx < graph.vertices.size(); vertex_idx++) {
        MVector random_dir(rand(), rand(), rand());
        orientation_field->representative_vectors.push_back(project_on_plane(random_dir, graph.vertices[vertex_idx].normal));
    }

    return MS::kSuccess;
}

int* MeshOperations::get_pair_of_rotations(int so, MVector oi, MVector oj, MVector ni, MVector nj)
{
    int best_rotations[2] = {0, 0};
    double best_angle = INFINITY;


    for (int k = 0; k < so; k++) {
        for (int l = 0; l < so; l++) {
            MVector Rso_i = Rso(so, oi, ni, k).normal();
            MVector Rso_j = Rso(so, oj, nj, l).normal();
            double angle = pow(angle_between_normalized(Rso_i, Rso_j), 2);
            if (angle < best_angle) {
                best_rotations[0] = k;
                best_rotations[1] = l;
                best_angle = angle;
            }
        }
    }

    return best_rotations;
}

MVector MeshOperations::Rso(int so, MVector o, MVector n, int k) {

    MTransformationMatrix m = {};
    double rotation_amount = k * 2.0 * M_PIl / so;
    m.setToRotationAxis(n, rotation_amount);
    return m.asMatrix() * o;

}

double MeshOperations::angle_between_normalized(MVector v1, MVector v2) {

    double angle = acos(v1 * v2);
    return angle;

}

MVector MeshOperations::project_on_plane(MVector v1, MVector plane_normal) {
    return v1 - ((v1 * plane_normal) / (plane_normal * plane_normal)) * plane_normal;
}