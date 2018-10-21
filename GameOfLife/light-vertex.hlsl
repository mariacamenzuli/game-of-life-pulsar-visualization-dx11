// Global Variables
cbuffer TransformationMatricesBuffer {
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};

// Type Definitions
// - Input
struct VertexDescriptor {
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

// - Output
struct PixelDescriptor {
    float4 screenSpacePosition : SV_POSITION;
    float4 worldSpacePosition : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

PixelDescriptor transformToScreenSpace(VertexDescriptor vertex) {
    PixelDescriptor pixel;

    // Set the w component (since it is not going to be passed along to the shader)
    vertex.position.w = 1.0f;

    // Calculate the screen space position of the vertex against the world, view, and projection matrices
    pixel.worldSpacePosition = mul(vertex.position, worldMatrix);
    pixel.screenSpacePosition = mul(pixel.worldSpacePosition, viewMatrix);
    pixel.screenSpacePosition = mul(pixel.screenSpacePosition, projectionMatrix);

    // Store the texture coordinates for the pixel shader.
    pixel.tex = vertex.tex;

    // Calculate the normal vector against the world matrix only
    pixel.normal = mul(vertex.normal, (float3x3) worldMatrix);

    // Normalize the normal vector.
    pixel.normal = normalize(pixel.normal);

    return pixel;
}