#pragma once

#include <wrl/client.h>
#include <d3dx10.h>

class Model {
public:
	struct Vertex {
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	Vertex* vertices;
	unsigned long* indices;
	int vertexCount, indexCount;

	Model();
	~Model();
};
