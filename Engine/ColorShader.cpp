#include <stdexcept>
#include <d3dx11async.h>

#include "ColorShader.h"

ColorShader::ColorShader() = default;

void ColorShader::compile(ID3D11Device* device, WCHAR* vsFilename, WCHAR* psFilename) {
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;
	Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer;
	Microsoft::WRL::ComPtr<ID3D10Blob> pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Compile the vertex shader code.
	result = D3DX11CompileFromFile(vsFilename, nullptr, nullptr, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr,
								   vertexShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf(), nullptr);
	if (FAILED(result)) {
		if (errorMessage) {
			throw std::runtime_error(static_cast<char*>(errorMessage->GetBufferPointer()));
		} else {
			throw std::runtime_error("Failed to create color shader. Missing vertex shader file.");
		}
	}

	// Compile the pixel shader code.
	result = D3DX11CompileFromFile(psFilename, nullptr, nullptr, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr,
								   pixelShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf(), nullptr);
	if (FAILED(result)) {
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage) {
			throw std::runtime_error(static_cast<char*>(errorMessage->GetBufferPointer()));
		} else {
			throw std::runtime_error("Failed to create color shader. Missing pixel shader file.");
		}
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create color shader. Creation of vertex shader failed.");
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create color shader. Creation of pixel shader failed.");
	}

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
									   vertexShaderBuffer->GetBufferSize(), layout.GetAddressOf());
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create color shader. Creation of input layout failed.");
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, matrixBuffer.GetAddressOf());
	if (FAILED(result)) {
		throw std::runtime_error("Failed to create color shader. Creation of matrix buffer failed.");
	}
}

void ColorShader::prepareShaderInput(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix) {
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;


	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		throw std::runtime_error("Failed to prepare shader input to render frame.");
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = static_cast<MatrixBufferType*>(mappedResource.pData);

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(matrixBuffer.Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, matrixBuffer.GetAddressOf());



	deviceContext->IASetInputLayout(layout.Get());
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
}
