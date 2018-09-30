#pragma once

#include <d3d11.h>

#include "Model.h"

class Scene {
public:
	Scene(ID3D11Device* device);
	~Scene();

	ID3D11Buffer* getVertexBuffer() const;
	ID3D11Buffer* getIndexBuffer() const;
	int getIndexCount();
	D3DXMATRIX getWorldMatrix();

private:
	struct SceneObject {
		Model model;
		D3DXMATRIX worldMatrix;

		SceneObject() {
			D3DXMatrixIdentity(&worldMatrix);
		};
	};
	SceneObject sceneObject;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};
