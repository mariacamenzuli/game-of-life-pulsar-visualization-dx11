#include "Material.h"

Material::Material() {
}

Material::~Material() = default;

D3DXVECTOR4 Material::getAmbientColor() const {
    return ambientColor;
}

D3DXVECTOR4 Material::getDiffuseColor() const {
    return diffuseColor;
}

D3DXVECTOR4 Material::getSpecularColor() const {
    return specularColor;
}

void Material::setAmbientColor(D3DXVECTOR4 ambientColor) {
    this->ambientColor = ambientColor;
}

void Material::setDiffuseColor(D3DXVECTOR4 diffuseColor) {
    this->diffuseColor = diffuseColor;
}

void Material::setSpecularColor(D3DXVECTOR4 specularColor) {
    this->specularColor = specularColor;
}
