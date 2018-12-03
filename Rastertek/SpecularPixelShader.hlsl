
struct Input
{
    float4 position : SV_POSITION;
    float2 texel : TEXCOORD;
    float3 normal : NORMAL;
    float3 viewDirection : VIEW_DIRECTION;
};

struct Output
{
    float4 color : SV_TARGET;
};

cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

Texture2D shaderTexture;
SamplerState sampleType;


Output main(Input input)
{
    Output output;
    float4 textureColor = shaderTexture.Sample(sampleType, input.texel);
    output.color = ambientColor;
    float3 direction = -lightDirection;
    float intensity = saturate(dot(input.normal, direction));

    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

    if (intensity > 0.0f)
    {
        output.color += diffuseColor * intensity;
        output.color = saturate(output.color);

        float3 reflection = normalize(2 * intensity * input.normal - direction);

        spec = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }

    output.color = output.color * textureColor;
    output.color = saturate(output.color + spec);

    return output;
}

