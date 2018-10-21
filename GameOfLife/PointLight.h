#pragma once

#include <D3DX10.h>

class PointLight {
public:
    PointLight();
    ~PointLight();

private:
    D3DXVECTOR4 diffuse;
    D3DXMATRIX worldMatrix;
};
