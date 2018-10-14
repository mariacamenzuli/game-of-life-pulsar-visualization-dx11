#pragma once

#include "Model.h"

class CubeModel : public Model {
public:
    CubeModel();
    ~CubeModel();

    int getVertexCount() override;
    int getIndexCount() override;
    Vertex* getVertices() override;
    unsigned long* getIndices() override;

private:
    const int vertexCount = 8;
    const int indexCount = 36;
    Vertex vertices[8];
    unsigned long indices[36];
};
