#pragma once

#include "Model.h"

#include <string>
#include <vector>
#include <regex>

class ObjModel : public Model {
public:
    ObjModel();
    ~ObjModel();

    static ObjModel loadFromFile(const std::string& filename, float vertexCorrectionX = 0.0f, float vertexCorrectionY = 0.0f, float vertexCorrectionZ = 0.0f);

    int getVertexCount() override;
    int getIndexCount() override;
    Vertex* getVertices() override;
    unsigned long* getIndices() override;
    Material* getMaterial() override;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned long> indices;
    Material material;

    static bool lineStartsWith(std::string text, std::string prefix);
    static Vertex createVertex(std::string vertexDescriptor, std::vector<D3DXVECTOR3>& vertexPositions, std::vector<D3DXVECTOR3>& normals, std::vector<D3DXVECTOR2>& textureCoordinates);
};

