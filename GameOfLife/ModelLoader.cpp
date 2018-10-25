#include "ModelLoader.h"
#include "ObjModel.h"
#include "CubeModel.h"

ModelLoader::ModelLoader() = default;

ModelLoader::~ModelLoader() = default;

Model* ModelLoader::getModel(ModelId modelId) {
    const auto found = modelMap.find(modelId);
    if (found != modelMap.end()) {
        return found->second.get();
    } else {
        Material material;
        switch (modelId) {
        case ModelId::CELL_CUBE:
            material.setAmbientColor(D3DXVECTOR4(0.0f, 0.2f, 0.0f, 1.0f));
            material.setDiffuseColor(D3DXVECTOR4(0.0f, 0.9f, 0.0f, 1.0f));
            material.setSpecularColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
            return modelMap.insert(std::make_pair(modelId, std::make_unique<CubeModel>(CubeModel(material)))).first->second.get();
        case ModelId::WORLD_BOARD:
            material.setAmbientColor(D3DXVECTOR4(0.4f, 0.6f, 0.4f, 1.0f));
            material.setDiffuseColor(D3DXVECTOR4(0.4f, 0.6f, 0.4f, 1.0f));
            material.setSpecularColor(D3DXVECTOR4(0.015532f, 0.005717f, 0.002170f, 1.0f));
            return modelMap.insert(std::make_pair(modelId, std::make_unique<CubeModel>(CubeModel(material)))).first->second.get();
        case ModelId::SUN:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/sun.obj", 0.0f, -40.0f, 17.0f)))).first->second.get();
        case ModelId::TREE:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/lowpolytree.obj")))).first->second.get();
        default:
            throw std::runtime_error("Tried to obtain reference to an unknown model");
        }
    }
}
