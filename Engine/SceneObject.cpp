#include "SceneObject.h"

SceneObject::SceneObject() {
	D3DXMatrixIdentity(&worldMatrix);
}

SceneObject::~SceneObject() = default;

Model* SceneObject::getModel() {
	return &model;
}

D3DXMATRIX* SceneObject::getWorldMatrix() {
	return &worldMatrix;
}
