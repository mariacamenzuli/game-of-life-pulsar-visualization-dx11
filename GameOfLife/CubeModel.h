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
    Material* getMaterial() override;
private:
    const int vertexCount = 36;
    const int indexCount = 36;
    Vertex vertices[36];
    unsigned long indices[36];
    Material material;
};
