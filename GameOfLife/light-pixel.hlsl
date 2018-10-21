// Global Variables
cbuffer AmbientLightBuffer {
    float4 ambientLightColor;
};

cbuffer PointLightBuffer {
    float4 position;
    float4 diffuse;
};

// Type Definitions
// - Input
struct PixelDescriptor {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

float4 colorPixel(PixelDescriptor pixel) : SV_TARGET {
    float4 pixelColor;

    pixelColor = ambientLightColor;

    return pixelColor;
}