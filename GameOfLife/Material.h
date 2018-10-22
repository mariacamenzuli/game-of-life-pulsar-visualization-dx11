#pragma once

#include <D3DX10.h>

class Material {
public:
    Material();
    Material(D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR4 specularColor);
    ~Material();

    D3DXVECTOR4 getAmbientColor() const;
    D3DXVECTOR4 getDiffuseColor() const;
    D3DXVECTOR4 getSpecularColor() const;

    void setAmbientColor(D3DXVECTOR4 ambientColor);
    void setDiffuseColor(D3DXVECTOR4 diffuseColor);
    void setSpecularColor(D3DXVECTOR4 specularColor);

private:
    D3DXVECTOR4 ambientColor;
    D3DXVECTOR4 diffuseColor; // used if there is no diffuse texture
    D3DXVECTOR4 specularColor;
};
