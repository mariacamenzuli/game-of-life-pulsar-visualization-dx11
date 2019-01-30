#pragma once

#include "../3D Components/Scene.h"
#include "ModelLoader.h"

class GameOfLifeSimulator : public Scene {
public:
    GameOfLifeSimulator();
    ~GameOfLifeSimulator();

    SceneObject* getRootSceneObject() override;
    D3DXVECTOR4 getAmbientLight() override;
    PointLight* getPointLight() override;
    void update(float deltaTime);
private:
    enum class CellState {
        ALIVE, DEAD
    };

    struct Cell {
        CellState state;
        SceneObject* sceneObject;

        void kill() {
            state = CellState::DEAD;
            sceneObject->hide();
        }

        void spawn() {
            state = CellState::ALIVE;
            sceneObject->show();
        }
    };

    ModelLoader modelLoader;
    std::unique_ptr<SceneObject> rootSceneObject;
    PointLight pointLight;
    Cell cells[17][17];
    int updateCount = 0;
};
