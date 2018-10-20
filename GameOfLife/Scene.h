#pragma once

#include "SceneObject.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual SceneObject* getRootSceneObject() = 0;
};
