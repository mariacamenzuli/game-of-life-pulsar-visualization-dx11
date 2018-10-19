#include <d3dx11async.h>
#include <stdexcept>

#include "LightShader.h"

LightShader::LightShader() = default;

LightShader::~LightShader() = default;

void LightShader::compile(ID3D11Device* device) {
    HRESULT result;
    Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;
    Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer;
    Microsoft::WRL::ComPtr<ID3D10Blob> pixelShaderBuffer;

    // Compile the vertex shader code.
    result = D3DX11CompileFromFile(L"../Engine/light-vertex.hlsl", nullptr, nullptr, "transformToScreenSpace", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr,
                                   vertexShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf(), nullptr);
    if (FAILED(result)) {
        if (errorMessage) {
            throw std::runtime_error(static_cast<char*>(errorMessage->GetBufferPointer()));
        } else {
            throw std::runtime_error("Failed to create light shader. Missing vertex shader file.");
        }
    }

    // Compile the pixel shader code.
    result = D3DX11CompileFromFile(L"../Engine/light-pixel.hlsl", nullptr, nullptr, "colorPixel", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr,
                                   pixelShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf(), nullptr);
    if (FAILED(result)) {
        if (errorMessage) {
            throw std::runtime_error(static_cast<char*>(errorMessage->GetBufferPointer()));
        } else {
            throw std::runtime_error("Failed to create light shader. Missing pixel shader file.");
        }
    }

    // Create the vertex shader from the buffer.
    result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
    if (FAILED(result)) {
        throw std::runtime_error("Failed to create light shader. Creation of vertex shader failed.");
    }

    // Create the pixel shader from the buffer.
    result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
    if (FAILED(result)) {
        throw std::runtime_error("Failed to create light shader. Creation of pixel shader failed.");
    }

    D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

    polygonLayout[0].SemanticName = "POSITION";
    polygonLayout[0].SemanticIndex = 0;
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[0].InputSlot = 0;
    polygonLayout[0].AlignedByteOffset = 0;
    polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[0].InstanceDataStepRate = 0;

    polygonLayout[1].SemanticName = "NORMAL";
    polygonLayout[1].SemanticIndex = 0;
    polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[1].InputSlot = 0;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[1].InstanceDataStepRate = 0;

    polygonLayout[2].SemanticName = "TEXCOORD";
    polygonLayout[2].SemanticIndex = 0;
    polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
    polygonLayout[2].InputSlot = 0;
    polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[2].InstanceDataStepRate = 0;

    // Get a count of the elements in the layout.
    unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    D3D11_BUFFER_DESC transformationMatricesBufferDesc;

    // Create the vertex input layout.
    result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
                                       vertexShaderBuffer->GetBufferSize(), layout.GetAddressOf());
    if (FAILED(result)) {
        throw std::runtime_error("Failed to create light shader. Creation of input layout failed.");
    }

    // Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
    transformationMatricesBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    transformationMatricesBufferDesc.ByteWidth = sizeof(TransformationMatricesBuffer);
    transformationMatricesBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transformationMatricesBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    transformationMatricesBufferDesc.MiscFlags = 0;
    transformationMatricesBufferDesc.StructureByteStride = 0;

    // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    result = device->CreateBuffer(&transformationMatricesBufferDesc, nullptr, transformationMatricesBuffer.GetAddressOf());
    if (FAILED(result)) {
        throw std::runtime_error("Failed to create light shader. Creation of transformation matrices constant buffer failed.");
    }

    D3D11_BUFFER_DESC ambientLightBufferDesc;

    ambientLightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    ambientLightBufferDesc.ByteWidth = sizeof(AmbientLightBuffer);
    ambientLightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ambientLightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ambientLightBufferDesc.MiscFlags = 0;
    ambientLightBufferDesc.StructureByteStride = 0;

    // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    result = device->CreateBuffer(&ambientLightBufferDesc, nullptr, ambientLightBuffer.GetAddressOf());
    if (FAILED(result)) {
        throw std::runtime_error("Failed to create light shader. Creation of transformation matrices constant buffer failed.");
    }
}

void LightShader::prepareShaderInput(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXVECTOR4 ambientLightColor) {
    HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    unsigned int bufferNumber;


    // Transpose the matrices to prepare them for the shader.
    D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
    D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
    D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

    // Lock the constant buffer so it can be written to.
    result = deviceContext->Map(transformationMatricesBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) {
        throw std::runtime_error("Failed to prepare shader input to render frame.");
    }

    // Get a pointer to the data in the constant buffer.
    TransformationMatricesBuffer* transformationMatrixData = static_cast<TransformationMatricesBuffer*>(mappedResource.pData);

    // Copy the matrices into the constant buffer.
    transformationMatrixData->world = worldMatrix;
    transformationMatrixData->view = viewMatrix;
    transformationMatrixData->projection = projectionMatrix;

    // Unlock the constant buffer.
    deviceContext->Unmap(transformationMatricesBuffer.Get(), 0);

    // Set the position of the constant buffer in the vertex shader.
    bufferNumber = 0;

    // Finanly set the constant buffer in the vertex shader with the updated values.
    deviceContext->VSSetConstantBuffers(bufferNumber, 1, transformationMatricesBuffer.GetAddressOf());

    // Lock the light constant buffer so it can be written to.
    result = deviceContext->Map(ambientLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) {
        throw std::runtime_error("Failed to prepare shader input to render frame.");
    }

    // Get a pointer to the data in the constant buffer.
    AmbientLightBuffer* ambientLightData = static_cast<AmbientLightBuffer*>(mappedResource.pData);

    // Copy the lighting variables into the constant buffer.
    ambientLightData->ambientLightColor = ambientLightColor;

    // Unlock the constant buffer.
    deviceContext->Unmap(ambientLightBuffer.Get(), 0);

    // Set the position of the light constant buffer in the pixel shader.
    bufferNumber = 0;

    // Finally set the light constant buffer in the pixel shader with the updated values.
    deviceContext->PSSetConstantBuffers(bufferNumber, 1, ambientLightBuffer.GetAddressOf());

    deviceContext->IASetInputLayout(layout.Get());
    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
}
