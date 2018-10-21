#pragma once

#include <D3DX10.h>

class Material {
public:
    Material();
    ~Material();

private:
    D3DXVECTOR4 diffuse;
};
