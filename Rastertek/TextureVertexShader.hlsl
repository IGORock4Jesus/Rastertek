
cbuffer Matrices
{
    matrix world, view, proj;
};

struct Input
{
    float4 position : POSITION;
    float2 texel: TEXCOORD0;
};

struct Output
{
    float4 position : SV_POSITION;
    float2 texel : TEXCOORD0;
};


Output main(Input input)
{
    Output output;
    input.position.w = 1.0f;

    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    output.texel = input.texel;

    return output;
}