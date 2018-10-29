#pragma once

#include <D3DX10.h>

class PointLight {
public:
    PointLight(D3DXVECTOR4 diffuse, D3DXVECTOR4 specular);
    ~PointLight();

    D3DXVECTOR4 getDiffuse();
    D3DXVECTOR4 getSpecular();
    D3DXMATRIX* getWorldMatrix();

    void translate(float x, float y, float z);
    void rotateX(float angleInRadians);
    void rotateY(float angleInRadians);
    void rotateZ(float angleInRadians);

    void getViewMatrix(D3DXMATRIX& viewMatrix);
    void getProjectionMatrix(D3DXMATRIX& projectionMatrix, float screenDepth, float screenNear);

private:
    D3DXVECTOR4 diffuse;
    D3DXVECTOR4 specular;
    D3DXMATRIX worldMatrix;

    D3DXVECTOR3 lookAtPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};
