#pragma once

#include <D3DX10.h>

#include "Model.h"

class SceneObject {
public:
	SceneObject();
	~SceneObject();

	Model* getModel();
	D3DXMATRIX* getWorldMatrix();

private:
	Model model;
	D3DXMATRIX worldMatrix;
};
