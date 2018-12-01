
struct Input
{
    float4 position : SV_POSITION;
    float2 texel : TEXCOORD;
    float3 normal : NORMAL;
};

struct Output
{
    float4 color : SV_TARGET;
};

cbuffer LightBuffer
{
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
};

Texture2D shaderTexture;
SamplerState sampleType;


Output main(Input input)
{
    Output output;
    float4 textureColor = shaderTexture.Sample(sampleType, input.texel);
    float3 direction = -lightDirection;
    float intensity = saturate(dot(input.normal, direction));

    output.color = saturate(diffuseColor * intensity);

    output.color = output.color * textureColor;

    return output;
}

