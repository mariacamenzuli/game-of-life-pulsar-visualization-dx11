#include "Scene.h"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::addSceneObject(SceneObject* sceneObject) {
    sceneObjects.push_back(sceneObject);
}

std::vector<SceneObject*>* Scene::getSceneObjects() {
    return &sceneObjects;
}
