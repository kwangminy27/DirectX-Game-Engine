struct VS_OUTPUT_POSITION_TEX
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PS_OUTPUT_SINGLE_TARGET
{
	float4 target : SV_TARGET;
};

cbuffer Material : register(b1)
{
	float4 g_diffuse;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

PS_OUTPUT_SINGLE_TARGET BasicTexPS(VS_OUTPUT_POSITION_TEX input)
{
	PS_OUTPUT_SINGLE_TARGET output = (PS_OUTPUT_SINGLE_TARGET)0;

	output.target = /*float4(1.f, 1.f, 1.f, 1.f);*/g_texture.Sample(g_sampler, input.uv) * g_diffuse;

	return output;
}