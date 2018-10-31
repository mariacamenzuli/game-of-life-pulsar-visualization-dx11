#include "GameOfLifeSimulator.h"

GameOfLifeSimulator::GameOfLifeSimulator() : pointLight(D3DXVECTOR4(1.0f, 1.0f, 0.9f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.4f, 1.0f)) {
    rootSceneObject.reset(new SceneObject());

    auto world = rootSceneObject->attachChild(std::make_unique<SceneObject>(), "world");

    const auto worldBoardModel = modelLoader.getModel(ModelLoader::ModelId::WORLD_BOARD);
    auto worldBoard = world->attachChild(std::make_unique<SceneObject>(worldBoardModel), "world_board");
    worldBoard->scale(37.5f, 8.0f, 37.5f);
    worldBoard->translate(0.0f, -9.0f, 0.0f);

    auto trees = world->attachChild(std::make_unique<SceneObject>(), "trees");
    const auto treeModel = modelLoader.getModel(ModelLoader::ModelId::TREE);
    auto tree1 = trees->attachChild(std::make_unique<SceneObject>(treeModel));
    tree1->scale(6.0f, 6.0f, 6.0f);
    tree1->translate(0.0f, 10.0f, 0.0f);

    const auto cellModel = modelLoader.getModel(ModelLoader::ModelId::BUSH);
    auto cellCubes = world->attachChild(std::make_unique<SceneObject>(), "cells");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            auto cellBush = cellCubes->attachChild(std::make_unique<SceneObject>(cellModel));
            cells[i][j] = { CellState::DEAD, cellBush };
            cells[i][j].kill();
            const auto random = rand() % 10 + 1;
            cellBush->rotateY(random / 10.0f);
            cellBush->scale(0.04f, 0.04f, 0.04f);
            cellBush->translate((i * 4.5) - 36.0f, 0.0f, (j * 4.5) - 36.0f);
        }
    }

    world->rotateY(0.785398);

    // Create a pulsar pattern
    cells[2][4].spawn();
    cells[2][5].spawn();
    cells[2][6].spawn();
    cells[2][10].spawn();
    cells[2][11].spawn();
    cells[2][12].spawn();

    cells[4][2].spawn();
    cells[4][7].spawn();
    cells[4][9].spawn();
    cells[4][14].spawn();

    cells[5][2].spawn();
    cells[5][7].spawn();
    cells[5][9].spawn();
    cells[5][14].spawn();

    cells[6][2].spawn();
    cells[6][7].spawn();
    cells[6][9].spawn();
    cells[6][14].spawn();

    cells[7][4].spawn();
    cells[7][5].spawn();
    cells[7][6].spawn();
    cells[7][10].spawn();
    cells[7][11].spawn();
    cells[7][12].spawn();

    cells[9][4].spawn();
    cells[9][5].spawn();
    cells[9][6].spawn();
    cells[9][10].spawn();
    cells[9][11].spawn();
    cells[9][12].spawn();

    cells[10][2].spawn();
    cells[10][7].spawn();
    cells[10][9].spawn();
    cells[10][14].spawn();

    cells[11][2].spawn();
    cells[11][7].spawn();
    cells[11][9].spawn();
    cells[11][14].spawn();

    cells[12][2].spawn();
    cells[12][7].spawn();
    cells[12][9].spawn();
    cells[12][14].spawn();

    cells[14][4].spawn();
    cells[14][5].spawn();
    cells[14][6].spawn();
    cells[14][10].spawn();
    cells[14][11].spawn();
    cells[14][12].spawn();

    const auto sunModel = modelLoader.getModel(ModelLoader::ModelId::SUN);
    auto sun = rootSceneObject->attachChild(std::make_unique<SceneObject>(sunModel), "sun");
    sun->translate(0.0f, 0.0f, 150.0f);
    sun->rotateX(1.5708f);

    pointLight.translate(0.0f, 0.0f, 100.0f);
    pointLight.rotateX(1.5708f);
}

GameOfLifeSimulator::~GameOfLifeSimulator() = default;

SceneObject* GameOfLifeSimulator::getRootSceneObject() {
    return rootSceneObject.get();
}

D3DXVECTOR4 GameOfLifeSimulator::getAmbientLight() {
    return D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
}

PointLight* GameOfLifeSimulator::getPointLight() {
    return &pointLight;
}

void GameOfLifeSimulator::update(float deltaTime) {
    updateCount++;

    rootSceneObject->getChild("world")->rotateY(0.01f * deltaTime);

    rootSceneObject->getChild("sun")->rotateX(-0.3f * deltaTime);
    pointLight.rotateX(-0.3f * deltaTime);

    std::vector<Cell*> toKill;
    std::vector<Cell*> toSpawn;

    if (updateCount % 1256 == 0) {
        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 17; j++) {
                int liveNeighbors = 0;
    
                if (i > 0) {
                    if (cells[i - 1][j].state == CellState::ALIVE) {
                        liveNeighbors++;
                    }
    
                    if (j > 0) {
                        if (cells[i - 1][j - 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                    
                    if (j < 16) {
                        if (cells[i - 1][j + 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                }
    
                if (i < 16) {
                    if (cells[i + 1][j].state == CellState::ALIVE) {
                        liveNeighbors++;
                    }
    
                    if (j > 0) {
                        if (cells[i + 1][j - 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                    
                    if (j < 16) {
                        if (cells[i + 1][j + 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                }
    
                if (j > 0) {
                    if (cells[i][j - 1].state == CellState::ALIVE) {
                        liveNeighbors++;
                    }
                }
                
                if (j < 16) {
                    if (cells[i][j + 1].state == CellState::ALIVE) {
                        liveNeighbors++;
                    }
                }
    
                if (cells[i][j].state == CellState::ALIVE) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        toKill.push_back(&cells[i][j]);
                    }
                } else if (liveNeighbors == 3) {
                    toSpawn.push_back(&cells[i][j]);
                }
            }
        }
    
        for (auto cell : toKill) {
            cell->kill();
        }
    
        for (auto cell : toSpawn) {
            cell->spawn();
        }
    }
}
