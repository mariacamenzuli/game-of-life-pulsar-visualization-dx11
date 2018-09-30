#include <stdexcept>

#include "Scene.h"

Scene::Scene() {
	
}

Scene::~Scene() = default;

void Scene::addSceneObject(SceneObject* sceneObject) {
	sceneObjects.push_back(sceneObject);

	for (int i = 0; i < sceneObject->getModel()->vertexCount; i++) {
		vertices.push_back(sceneObject->getModel()->vertices[i]);
	}
	for (int i = 0; i < sceneObject->getModel()->indexCount; i++) {
		indices.push_back(sceneObject->getModel()->indices[i]);
	}
}

int Scene::getIndexCount() {
	int indexCount = 0;
	for (auto sceneObject : sceneObjects) {
		indexCount = indexCount + sceneObject->getModel()->indexCount;
	}
	return indexCount;
}

int Scene::getVertexCount() {
	int vertexCount = 0;
	for (auto sceneObject : sceneObjects) {
		vertexCount = vertexCount + sceneObject->getModel()->vertexCount;
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
