#include "ObjModel.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

const std::regex regexPositionOnly(R"((\d+(?:\.\d+)?))");
const std::regex regexPositionAndTexture(R"((\d+(?:\.\d+)?)\/(\d+(?:\.\d+)?))");
const std::regex regexPositionAndNormal(R"((\d+(?:\.\d+)?)\/\/(\d+(?:\.\d+)?))");
const std::regex regexPositionTextureNormal(R"((\d+(?:\.\d+)?)\/(\d+(?:\.\d+)?)\/(\d+(?:\.\d+)?))");

ObjModel::ObjModel() = default;

ObjModel::~ObjModel() = default;

ObjModel ObjModel::loadFromFile(const std::string& filename) {
    std::ifstream inputStream;

    inputStream.open(filename);

    if (inputStream.fail()) {
        throw std::runtime_error("Failed to open file [" + filename + "] to load .obj model");
    }

    std::vector<D3DXVECTOR3> vertexPositions;
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

        if (lineStartsWith(line, "mtllib ")) {
            // todo handle material loading
        }

        if (lineStartsWith(line, "v ")) {
            std::istringstream stringStream(line.substr(2));
            D3DXVECTOR3 vertex;
            stringStream >> vertex.x >> vertex.y >> vertex.z;
            // Invert the Z vertex to change to left hand system.
            vertex.z = vertex.z * -1.0f;
            vertexPositions.push_back(vertex);
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
                auto vertex1 = createVertex(faceVertices.at(i), vertexPositions, normals, textureCoordinates);
                model.vertices.push_back(vertex1);
                model.indices.push_back(indexCount);
                indexCount++;

                auto vertex2 = createVertex(faceVertices.at(i - 1), vertexPositions, normals, textureCoordinates);
                model.vertices.push_back(vertex2);
                model.indices.push_back(indexCount);
                indexCount++;

                auto vertex3 = createVertex(faceVertices.at(0), vertexPositions, normals, textureCoordinates);
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

Model::Vertex ObjModel::createVertex(std::string vertexDescriptor, std::vector<D3DXVECTOR3>& vertexPositions, std::vector<D3DXVECTOR3>& normals, std::vector<D3DXVECTOR2>& textureCoordinates) {
    Vertex vertex;
    std::smatch regexMatches;

    if (std::regex_search(vertexDescriptor, regexMatches, regexPositionTextureNormal)) {
        vertex.position = vertexPositions[std::stoi(regexMatches[1]) - 1];
        vertex.texture = textureCoordinates[std::stoi(regexMatches[2]) - 1];
        vertex.normal = normals[std::stoi(regexMatches[3]) - 1];
    } else if (std::regex_search(vertexDescriptor, regexMatches, regexPositionAndNormal)) {
        vertex.position = vertexPositions[std::stoi(regexMatches[1]) - 1];
        vertex.texture.x = 0.0f;
        vertex.texture.y = 0.0f;
        vertex.normal = normals[std::stoi(regexMatches[2]) - 1];
    } else if (std::regex_search(vertexDescriptor, regexMatches, regexPositionAndTexture)) {
        vertex.position = vertexPositions[std::stoi(regexMatches[1]) - 1];
        vertex.texture = textureCoordinates[std::stoi(regexMatches[2]) - 1];
        vertex.normal.x = 0.0f;
        vertex.normal.y = 0.0f;
        vertex.normal.z = 0.0f;
    } else {
        vertex.position = vertexPositions[std::stoi(vertexDescriptor) - 1];
        vertex.texture.x = 0.0f;
        vertex.texture.y = 0.0f;
    }

    return vertex;
}
