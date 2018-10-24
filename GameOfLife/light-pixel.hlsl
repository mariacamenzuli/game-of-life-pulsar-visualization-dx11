cbuffer AmbientLightBuffer {
    float4 sceneAmbientColor;
};

cbuffer PointLightBuffer {
    float4 pointLightPosition;
    float4 pointLightDiffuse;
    float4 pointLightSpecular;
};

cbuffer MaterialBuffer {
    float4 materialAmbientColor;
    float4 materialDiffuseColor;
    float4 materialSpecularColor; // w component is specular power
};

// Type Definitions
// - Input
struct PixelDescriptor {
    float4 screenSpacePosition : SV_POSITION;
    float4 worldSpacePosition : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
    float3 viewDirection : VIEWDIR;
};

float4 sceneAmbience() {
    return materialAmbientColor * sceneAmbientColor;
}

float4 pointLight(PixelDescriptor pixel) {
    float4 color = 0;
    float lightIntensity;

    float3 pointToLightVector = pointLightPosition - pixel.worldSpacePosition;
    float pointToLightVectorLength = length(pointToLightVector);

    // make unit vector
    pointToLightVector /= pointToLightVectorLength;

    lightIntensity = saturate(dot(pixel.normal, pointToLightVector)); //todo: to saturate or not to saturate? when should we saturate?
    if (lightIntensity > 0.0f) {
        color += (lightIntensity * materialDiffuseColor * pointLightDiffuse);

        float3 reflection = normalize(2 * lightIntensity * pixel.normal - pointToLightVector);
        float specularFactor = pow(saturate(dot(reflection, pixel.viewDirection)), materialSpecularColor.w);;

        color += specularFactor * materialSpecularColor * pointLightSpecular;
    }

    return color;
}

float4 colorPixel(PixelDescriptor pixel) : SV_TARGET {
    float4 pixelColor = 0;

    // start out with the ambient color
    pixelColor += sceneAmbience();

    // add any diffuse light from point light
    pixelColor += pointLight(pixel);

    return pixelColor;
}