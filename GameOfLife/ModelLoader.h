#pragma once

#include <map>
#include <memory>

#include "Model.h"

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader();

    enum class ModelId {
        CUBE,
        SUN,
        TREE
    };

    Model* getModel(ModelId modelId);

private:
    std::map<ModelId, std::unique_ptr<Model>> modelMap;
};

