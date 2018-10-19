#pragma once

#include <D3DX10.h>

class Material {
public:
    Material();
    ~Material();

private:
    float specularPower;
    float transparency;
    D3DXVECTOR3 diffuseColor;
    D3DXVECTOR3 specularColor;
};
