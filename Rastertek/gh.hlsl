
cbuffer Matrices : register(b0)
{
    matrix world, view, proj;
};

cbuffer Camera : register(b1)
{
    float3 cameraPosition;
    float padding;
};

struct Input
{
    float4 position : POSITION;
    float2 texel: TEXCOORD;
    float3 normal : NORMAL;
};

struct Output
{
    float4 position : SV_POSITION;
    float2 texel : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
};


Output main(Input input)
{
    Output output;
    input.position.w = 1.0f;

    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    output.texel = input.texel;

    output.normal = mul(input.normal, (float3x3) world);
    output.normal = normalize(output.normal);

    float4 worldPosition = mul(input.position, world);
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);

    return output;
}