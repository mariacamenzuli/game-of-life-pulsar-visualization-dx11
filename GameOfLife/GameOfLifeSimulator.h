#pragma once

#include "Scene.h"
#include "ModelLoader.h"

class GameOfLifeSimulator : public Scene {
public:
    GameOfLifeSimulator();
    ~GameOfLifeSimulator();

    SceneObject* getRootSceneObject() override;
    D3DXVECTOR4 getAmbientLight() override;
    void update(float deltaTime);
private:
    enum class CellState {
        ALIVE, DEAD
    };

    struct Cell {
        CellState state;
        SceneObject* sceneObject;
    };

    ModelLoader modelLoader;
    std::unique_ptr<SceneObject> rootSceneObject;
    Cell cells[10][31];
};
