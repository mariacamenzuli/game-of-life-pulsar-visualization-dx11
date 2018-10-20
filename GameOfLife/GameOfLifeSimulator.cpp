#include "GameOfLifeSimulator.h"

GameOfLifeSimulator::GameOfLifeSimulator() {
    auto cubeModel = modelLoader.getModel(ModelLoader::ModelId::CUBE);
    rootSceneObject.reset(new SceneObject(cubeModel));
    rootSceneObject->scale(12.0f, 12.0f, 12.0f);
}

GameOfLifeSimulator::~GameOfLifeSimulator() = default;

SceneObject* GameOfLifeSimulator::getRootSceneObject() {
    return rootSceneObject.get();
}

void GameOfLifeSimulator::update(float deltaTime) {
}
