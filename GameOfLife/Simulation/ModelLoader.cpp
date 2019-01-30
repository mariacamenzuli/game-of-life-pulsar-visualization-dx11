#include "ModelLoader.h"
#include "../3D Components/Models/ObjModel.h"
#include "../3D Components/Models/CubeModel.h"

ModelLoader::ModelLoader() = default;

ModelLoader::~ModelLoader() = default;

Model* ModelLoader::getModel(ModelId modelId) {
    const auto found = modelMap.find(modelId);
    if (found != modelMap.end()) {
        return found->second.get();
    } else {
        const Material worldBoardMaterial(D3DXVECTOR4(0.4f, 0.6f, 0.4f, 1.0f), D3DXVECTOR4(0.4f, 0.6f, 0.4f, 1.0f), D3DXVECTOR4(0.015532f, 0.005717f, 0.002170f, 1.0f), "Resources/Textures/dirt-stones.dds");
        switch (modelId) {
        case ModelId::WORLD_BOARD:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<CubeModel>(CubeModel(worldBoardMaterial)))).first->second.get();
        case ModelId::BUSH:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/bush.obj")))).first->second.get();
        case ModelId::SUN:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/sun.obj", 0.0f, -40.0f, 17.0f)))).first->second.get();
        case ModelId::TREE:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/lowpolytree.obj")))).first->second.get();
        default:
            throw std::runtime_error("Tried to obtain reference to an unknown model");
        }
    }
}
