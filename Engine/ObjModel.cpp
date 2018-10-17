#include "ObjModel.h"

#include <fstream>
#include <sstream>
#include <vector>

ObjModel::ObjModel() {
}

ObjModel::~ObjModel() = default;

ObjModel ObjModel::loadFromFile(const std::string& filename) {
    std::ifstream inputStream;

    inputStream.open(filename);

    if (inputStream.fail()) {
        throw std::runtime_error("Failed to open file [" + filename + "] to load .obj model");
    }

    std::vector<D3DXVECTOR3> verticesPositions;
    std::vector<D3DXVECTOR3> normals;
    std::vector<D3DXVECTOR2> textureCoordinates;

    ObjModel model;

    int indexCount = 0;
    while (!inputStream.eof()) {
        std::string line;
        std::getline(inputStream, line);

        if (line.empty()) {
            continue;
        }

        if (lineStartsWith(line, "v ")) {
            std::istringstream stringStream(line.substr(2));
            D3DXVECTOR3 vertex;
            stringStream >> vertex.x >> vertex.y >> vertex.z;
            // Invert the Z vertex to change to left hand system.
            vertex.z = vertex.z * -1.0f;
            verticesPositions.push_back(vertex);
        }

        if (lineStartsWith(line, "vn ")) {
            std::istringstream stringStream(line.substr(3));
            D3DXVECTOR3 normal;
            stringStream >> normal.x >> normal.y >> normal.z;
            // Invert the Z normal to change to left hand system.
            normal.z = normal.z * -1.0f;
            normals.push_back(normal);
        }

        if (lineStartsWith(line, "vt ")) {
            std::istringstream stringStream(line.substr(3));
            D3DXVECTOR2 textureCoordinate;
            stringStream >> textureCoordinate.x >> textureCoordinate.y;
            // Invert the V texture coordinates to left hand system.
            textureCoordinate.y = 1.0f - textureCoordinate.y;
            textureCoordinates.push_back(textureCoordinate);
        }

        if (lineStartsWith(line, "f ")) {
            std::istringstream stringStream(line.substr(2));
            std::vector<std::string> faceVertices;
            std::string faceVertex;
            while (stringStream.rdbuf()->in_avail() != 0) {
                stringStream >> faceVertex;
                faceVertices.push_back(faceVertex);
            }
            
            for (int i = faceVertices.size() - 1; i > 1; i--) {
                int vertexIndex1 = std::stoi(faceVertices.at(i).substr(0, faceVertices.at(i).find('/')));
                Vertex vertex1;
                vertex1.position = verticesPositions[vertexIndex1 - 1]; // - 1 because the indices are 1 based, not 0 based
                vertex1.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
                model.vertices.push_back(vertex1);
                model.indices.push_back(indexCount);
                indexCount++;

                int vertexIndex2 = std::stoi(faceVertices.at(i - 1).substr(0, faceVertices.at(i - 1).find('/')));
                Vertex vertex2;
                vertex2.position = verticesPositions[vertexIndex2 - 1];
                vertex2.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
                model.vertices.push_back(vertex2);
                model.indices.push_back(indexCount);
                indexCount++;

                int vertexIndex3 = std::stoi(faceVertices.at(0).substr(0, faceVertices.at(0).find('/')));
                Vertex vertex3;
                vertex3.position = verticesPositions[vertexIndex3 - 1];
                vertex3.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
                model.vertices.push_back(vertex3);
                model.indices.push_back(indexCount);
                indexCount++;
            }
        }
    }

    inputStream.close();

    return model;
}

int ObjModel::getVertexCount() {
    return vertices.size();
}

int ObjModel::getIndexCount() {
    return indices.size();
}

Model::Vertex* ObjModel::getVertices() {
    return vertices.data();
}

unsigned long* ObjModel::getIndices() {
    return indices.data();
}

bool ObjModel::lineStartsWith(std::string text, std::string prefix) {
    return text.find(prefix) == 0;
}
