#pragma once

#include <vector>

#include "Model.h"
#include "SceneObject.h"

class Scene {
public:
	Scene();
	~Scene();

	int getIndexCount();
	int getVertexCount();
	Model::Vertex* getVertices();
	unsigned long* getIndices();

	void addSceneObject(SceneObject* sceneObject);
	std::vector<SceneObject*>* getSceneObjects();

private:
	std::vector<SceneObject*> sceneObjects;
	std::vector<Model::Vertex> vertices;
	std::vector<unsigned long> indices;
};
