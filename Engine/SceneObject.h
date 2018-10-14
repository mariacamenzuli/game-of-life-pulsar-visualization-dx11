#pragma once

#include <D3DX10.h>

#include "Model.h"

class SceneObject {
public:
    SceneObject(Model* model);
    ~SceneObject();

    Model* getModel();
    D3DXMATRIX* getWorldMatrix();

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotateX(float angleInRadians);
    void rotateY(float angleInRadians);
    void rotateZ(float angleInRadians);

private:
    Model* model;
    D3DXMATRIX worldMatrix;
};
