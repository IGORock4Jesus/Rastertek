
struct Input
{
    float4 position : SV_POSITION;
    float2 texel : TEXCOORD;
};

struct Output
{
    float4 color : SV_TARGET;
};

Texture2D shaderTexture;
SamplerState sampleType;


Output main(Input input)
{
    Output output;
    output.color = shaderTexture.Sample(sampleType, input.texel);
    return output;
}

