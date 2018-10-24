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

private:
    D3DXVECTOR4 diffuse;
    D3DXVECTOR4 specular;
    D3DXMATRIX worldMatrix;
};
