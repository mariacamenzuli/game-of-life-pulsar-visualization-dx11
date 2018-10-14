#include "CubeModel.h"

CubeModel::CubeModel() {
    vertices[0].position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
    vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[1].position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
    vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[2].position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
    vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[3].position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
    vertices[3].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[4].position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
    vertices[4].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[5].position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
    vertices[5].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[6].position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
    vertices[6].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[7].position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
    vertices[7].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

    // top face
    indices[0] = 1;
    indices[1] = 2;
    indices[2] = 0;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    //side face +ve z
    indices[6] = 3;
    indices[7] = 4;
    indices[8] = 0;
    indices[9] = 4;
    indices[10] = 3;
    indices[11] = 7;

    //side face -ve x
    indices[12] = 2;
    indices[13] = 7;
    indices[14] = 3;
    indices[15] = 2;
    indices[16] = 6;
    indices[17] = 7;

    //side face -ve z
    indices[18] = 6;
    indices[19] = 1;
    indices[20] = 5;
    indices[21] = 6;
    indices[22] = 2;
    indices[23] = 1;

    //side face +ve x
    indices[24] = 1;
    indices[25] = 0;
    indices[26] = 4;
    indices[27] = 1;
    indices[28] = 4;
    indices[29] = 5;

    //bottom face
    indices[30] = 6;
    indices[31] = 5;
    indices[32] = 4;
    indices[33] = 6;
    indices[34] = 4;
    indices[35] = 7;
}

CubeModel::~CubeModel() = default;

int CubeModel::getVertexCount() {
    return vertexCount;
}

int CubeModel::getIndexCount() {
    return indexCount;
}

Model::Vertex* CubeModel::getVertices() {
    return vertices;
}

unsigned long* CubeModel::getIndices() {
    return indices;
}
