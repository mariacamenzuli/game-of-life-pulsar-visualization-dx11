#include <stdexcept>

#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() = default;

void Scene::addSceneObject(SceneObject* sceneObject) {
    sceneObjects.push_back(sceneObject);

    for (int i = 0; i < sceneObject->getModel()->getVertexCount(); i++) {
        vertices.push_back(sceneObject->getModel()->getVertices()[i]);
    }
    for (int i = 0; i < sceneObject->getModel()->getIndexCount(); i++) {
        indices.push_back(sceneObject->getModel()->getIndices()[i]);
    }
}

int Scene::getIndexCount() {
    int indexCount = 0;
    for (auto sceneObject : sceneObjects) {
        indexCount = indexCount + sceneObject->getModel()->getIndexCount();
    }
    return indexCount;
}

int Scene::getVertexCount() {
    int vertexCount = 0;
    for (auto sceneObject : sceneObjects) {
        vertexCount = vertexCount + sceneObject->getModel()->getVertexCount();
    }
    return vertexCount;
}

std::vector<SceneObject*>* Scene::getSceneObjects() {
    return &sceneObjects;
}

Model::Vertex* Scene::getVertices() {
    return vertices.data();
}

unsigned long* Scene::getIndices() {
    return indices.data();
}
