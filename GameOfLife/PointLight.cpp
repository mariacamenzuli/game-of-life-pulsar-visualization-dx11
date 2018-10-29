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

void PointLight::getViewMatrix(D3DXMATRIX& viewMatrix) {
    D3DXVECTOR3 up(0.0f, 0.1f, 0.0f);
    D3DXVECTOR3 position3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    D3DXVECTOR4 position4;
    D3DXVec3Transform(&position4, &position3, &worldMatrix);
    position3.x = position4.x / position4.w;
    position3.y = position4.y / position4.w;
    position3.z = position4.z / position4.w;
    D3DXMatrixLookAtLH(&viewMatrix, &position3, &lookAtPoint, &up);
}

void PointLight::getProjectionMatrix(D3DXMATRIX& projectionMatrix, float screenDepth, float screenNear) {
    // Setup field of view and screen aspect for a square light source.
    float fieldOfView = static_cast<float>(D3DX_PI) / 2.0f;
    float screenAspect = 1.0f;

    D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
}
