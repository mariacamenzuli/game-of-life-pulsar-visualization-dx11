#include "GameOfLifeSimulator.h"

GameOfLifeSimulator::GameOfLifeSimulator() : pointLight(D3DXVECTOR4(1.0f, 1.0f, 0.9f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.4f, 1.0f)) {
    rootSceneObject.reset(new SceneObject());

    const auto worldCubeModel = modelLoader.getModel(ModelLoader::ModelId::WORLD_CUBE);
    auto worldCube = rootSceneObject->attachChild(std::make_unique<SceneObject>(worldCubeModel), "world_cube");
    worldCube->scale(11.0f, 12.0f, 11.0f);

    const auto cellCubeModel = modelLoader.getModel(ModelLoader::ModelId::CELL_CUBE);
    auto cellCubes = rootSceneObject->attachChild(std::make_unique<SceneObject>(), "cell_cubes");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cellCubeModel));
            cells[i][j] = { CellState::DEAD, cellCube };
            cells[i][j].kill();
            cellCube->translate((i * 2) - 9.0f, (j * 2) - 6, 12.0f);
        }
    
        for (int j = 10; j < 21; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cellCubeModel));
            cells[i][j] = { CellState::DEAD, cellCube };
            cells[i][j].kill();
            cellCube->translate((i * 2) - 9.0f, 14.0f, (j * 2) - 30.0f);
        }
    
        for (int j = 21; j < 31; j++) {
            auto cellCube = cellCubes->attachChild(std::make_unique<SceneObject>(cellCubeModel));
            cells[i][j] = { CellState::DEAD, cellCube };
            cells[i][j].kill();
            cellCube->translate((i * 2) - 9.0f, 12.0f - ((j - 21.0f) * 2.0f), -12.0f);
        }
    }

    cellCubes->rotateY(0.785398);
    worldCube->rotateY(0.785398);

    cells[4][12].spawn();
    cells[4][17].spawn();
    cells[5][10].spawn();
    cells[5][11].spawn();
    cells[5][13].spawn();
    cells[5][14].spawn();
    cells[5][15].spawn();
    cells[5][16].spawn();
    cells[5][18].spawn();
    cells[5][19].spawn();
    cells[6][12].spawn();
    cells[6][17].spawn();

    const auto sunModel = modelLoader.getModel(ModelLoader::ModelId::SUN);
    auto sun = rootSceneObject->attachChild(std::make_unique<SceneObject>(sunModel), "sun");
    sun->translate(0.0f, 0.0f, 100.0f);

    pointLight.translate(0.0f, 0.0f, 75.0f);
}

GameOfLifeSimulator::~GameOfLifeSimulator() = default;

SceneObject* GameOfLifeSimulator::getRootSceneObject() {
    return rootSceneObject.get();
}

D3DXVECTOR4 GameOfLifeSimulator::getAmbientLight() {
    return D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

PointLight* GameOfLifeSimulator::getPointLight() {
    return &pointLight;
}

void GameOfLifeSimulator::update(float deltaTime) {
    updateCount++;

    rootSceneObject->getChild("sun")->rotateX(-0.1f * deltaTime);
    pointLight.rotateX(-0.1f * deltaTime);

    std::vector<Cell*> toKill;
    std::vector<Cell*> toSpawn;

    if (updateCount % 120 == 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 31; j++) {
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
                    
                    if (j < 30) {
                        if (cells[i - 1][j + 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                }

                if (i < 9) {
                    if (cells[i + 1][j].state == CellState::ALIVE) {
                        liveNeighbors++;
                    }

                    if (j > 0) {
                        if (cells[i + 1][j - 1].state == CellState::ALIVE) {
                            liveNeighbors++;
                        }
                    }
                    
                    if (j < 30) {
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
                
                if (j < 30) {
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
