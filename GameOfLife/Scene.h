#pragma once

#include <vector>

#include "SceneObject.h"

class Scene {
public:
    Scene();
    ~Scene();

    void addSceneObject(SceneObject* sceneObject);
    std::vector<SceneObject*>* getSceneObjects();

private:
    std::vector<SceneObject*> sceneObjects;
};
