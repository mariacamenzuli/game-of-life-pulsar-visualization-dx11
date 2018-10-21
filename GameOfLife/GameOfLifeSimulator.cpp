#include "GameOfLifeSimulator.h"

GameOfLifeSimulator::GameOfLifeSimulator() {
    rootSceneObject.reset(new SceneObject());

    const auto cubeModel = modelLoader.getModel(ModelLoader::ModelId::CUBE);
    auto worldCube = rootSceneObject->attachChild(std::make_unique<SceneObject>(cubeModel), "world_cube");
    worldCube->scale(11.0f, 12.0f, 11.0f);

    auto cellCubes = rootSceneObject->attachChild(std::make_unique<SceneObject>(), "cell_cubes");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cubeModel));
            cells[i][j] = { CellState::ALIVE, cellCube };
            cellCube->translate((i * 2) - 9.0f, (j * 2) - 6, 12.0f);
        }

        for (int j = 10; j < 21; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cubeModel));
            cells[i][j] = { CellState::ALIVE, cellCube };
            cellCube->translate((i * 2) - 9.0f, 14.0f, (j * 2) - 30.0f);
        }

        for (int j = 21; j < 31; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cubeModel));
            cells[i][j] = { CellState::ALIVE, cellCube };
            cellCube->translate((i * 2) - 9.0f, 12.0f - ((j - 21) * 2), -12.0f);
        }
    }
}

GameOfLifeSimulator::~GameOfLifeSimulator() = default;

SceneObject* GameOfLifeSimulator::getRootSceneObject() {
    return rootSceneObject.get();
}

void GameOfLifeSimulator::update(float deltaTime) {
    rootSceneObject->rotateY(0.1f * deltaTime);
    rootSceneObject->rotateX(0.1f * deltaTime);
}
