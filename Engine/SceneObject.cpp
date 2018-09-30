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

void SceneObject::translate(float x, float y, float z) {
	D3DXMatrixTranslation(&worldMatrix, x, y, z);
}

void SceneObject::scale(float x, float y, float z) {
	D3DXMatrixScaling(&worldMatrix, x, y, z);
}

void SceneObject::rotateY(float angleInRadians) {
	D3DXMatrixRotationY(&worldMatrix, angleInRadians);
}

void SceneObject::rotateX(float angleInRadians) {
	D3DXMatrixRotationX(&worldMatrix, angleInRadians);
}

void SceneObject::rotateZ(float angleInRadians) {
	D3DXMatrixRotationZ(&worldMatrix, angleInRadians);
}
