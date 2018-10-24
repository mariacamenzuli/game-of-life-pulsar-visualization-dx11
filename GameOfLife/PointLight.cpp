#include "PointLight.h"

PointLight::PointLight(const D3DXVECTOR4 diffuse, const D3DXVECTOR4 specular) : diffuse(diffuse), specular(specular) {
    D3DXMatrixIdentity(&worldMatrix);
};

PointLight::~PointLight() = default;

D3DXVECTOR4 PointLight::getDiffuse() {
    return diffuse;
}

D3DXVECTOR4 PointLight::getSpecular() {
    return specular;
}

D3DXMATRIX* PointLight::getWorldMatrix() {
    return &worldMatrix;
}

void PointLight::translate(float x, float y, float z) {
    D3DXMATRIX translationMatrix;
    D3DXMatrixTranslation(&translationMatrix, x, y, z);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
}

void PointLight::rotateX(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationX(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}

void PointLight::rotateY(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationY(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}

void PointLight::rotateZ(float angleInRadians) {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationZ(&rotationMatrix, angleInRadians);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotationMatrix);
}
