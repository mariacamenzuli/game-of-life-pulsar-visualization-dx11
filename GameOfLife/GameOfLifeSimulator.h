#pragma once

#include "Scene.h"
#include "ModelLoader.h"

class GameOfLifeSimulator : public Scene {
public:
    GameOfLifeSimulator();
    ~GameOfLifeSimulator();

    SceneObject* getRootSceneObject() override;
    void update(float deltaTime);
private:
    enum class Cell {
        ALIVE, DEAD
    };

    ModelLoader modelLoader;
    std::unique_ptr<SceneObject> rootSceneObject;
    Cell cells[10][3];
};
