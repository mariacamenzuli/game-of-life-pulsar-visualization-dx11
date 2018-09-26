#include <stdexcept>

#include "Scene.h"

Scene::Scene(ID3D11Device* device) {
	camera.setPosition(0.0f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Model::Vertex) * sceneObject.model.vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = sceneObject.model.vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create vertex buffer for scene.");
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * sceneObject.model.indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = sceneObject.model.indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create index buffer for scene.");
	}
}

Scene::~Scene() = default;

Camera* Scene::getCamera() {
	return &camera;
}

ID3D11Buffer* Scene::getVertexBuffer() const {
	return vertexBuffer.Get();
}

ID3D11Buffer* Scene::getIndexBuffer() const {
	return indexBuffer.Get();
}

int Scene::getIndexCount() {
	return sizeof(unsigned long) * sceneObject.model.indexCount;
}

D3DXMATRIX Scene::getWorldMatrix() {
	return sceneObject.worldMatrix;
}
