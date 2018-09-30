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
