#include "SceneObject.h"

SceneObject::SceneObject() {
    D3DXMatrixIdentity(&worldMatrix);
}

SceneObject::SceneObject(Model* model): model(model) {
    D3DXMatrixIdentity(&worldMatrix);
}

SceneObject::~SceneObject() = default;

Model* SceneObject::getModel() {
    return model;
}

D3DXMATRIX* SceneObject::getWorldMatrix() {
    return &worldMatrix;
}

D3DXMATRIX SceneObject::getCompositeWorldMatrix() {
    if (parent != nullptr) {
        D3DXMATRIX compositeWorldMatrix;
        D3DXMATRIX parentCompositeWorldMatrix = parent->getCompositeWorldMatrix();
        D3DXMatrixMultiply(&compositeWorldMatrix, &worldMatrix, &parentCompositeWorldMatrix);
        return compositeWorldMatrix;
    } else {
        return worldMatrix;
    }
}

SceneObject* SceneObject::attachChild(std::unique_ptr<SceneObject> child) {
    child->parent = this;
    children.push_back(std::move(child));
    return children.at(children.size() - 1).get();
}

SceneObject* SceneObject::attachChild(std::unique_ptr<SceneObject> child, std::string label) {
    auto childPtr = this->attachChild(std::move(child));
    labeledChildren.insert(std::make_pair(label, childPtr));
    return childPtr;
}

SceneObject* SceneObject::getChild(std::string label) {
    const auto found = labeledChildren.find(label);
    if (found == labeledChildren.end()) {
        return nullptr;
    }
    return found->second;
}

std::vector<SceneObject*> SceneObject::getChildren() {
    std::vector<SceneObject*> childPointers;

    for (auto& child : children) {
        childPointers.push_back(child.get());
    }

    return childPointers;
}

void SceneObject::translate(float x, float y, float z) {
    //todo: apply transformation to currentChildren
    D3DXMATRIX translationMatrix;
    D3DXMatrixTranslation(&translationMatrix, x, y, z);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
}

void SceneObject::scale(float x, float y, float z) {
    D3DXMATRIX scalingMatrix;
    D3DXMatrixScaling(&scalingMatrix, x, y, z);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
}

void SceneObject::rotateX(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationX(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}

void SceneObject::rotateY(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationY(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}

void SceneObject::rotateZ(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationZ(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}
