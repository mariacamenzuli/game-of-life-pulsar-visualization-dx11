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
        switch (modelId) {
        case ModelId::CUBE:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<CubeModel>(CubeModel()))).first->second.get();
        case ModelId::SUN:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/sun.obj", 0.0f, -40.0f, 17.0f)))).first->second.get();
        case ModelId::TREE:
            return modelMap.insert(std::make_pair(modelId, std::make_unique<ObjModel>(ObjModel::loadFromFile("Resources/Models/lowpolytree.obj")))).first->second.get();
        default:
            throw std::runtime_error("Tried to obtain reference to an unknown model");
        }
    }
}
