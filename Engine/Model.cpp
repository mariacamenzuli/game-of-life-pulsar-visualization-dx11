#include "Model.h"

Model::Model() {
    // Set the number of vertices in the vertex array.
    vertexCount = 3;

    // Set the number of indices in the index array.
    indexCount = 3;

    // Create the vertex array.
    vertices = new Vertex[vertexCount];

    // Create the index array.
    indices = new unsigned long[indexCount];

    // Load the vertex array with data.
    vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); // Bottom left.
    vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // Top middle.
    vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); // Bottom right.
    vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

    // Load the index array with data.
    indices[0] = 0; // Bottom left.
    indices[1] = 1; // Top middle.
    indices[2] = 2; // Bottom right.
}

Model::~Model() {
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;
}
