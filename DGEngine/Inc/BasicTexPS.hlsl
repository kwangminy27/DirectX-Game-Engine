struct VS_OUTPUT_POSITION_TEX
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PS_OUTPUT_SINGLE_TARGET
{
	float4 target : SV_TARGET;
};

cbuffer Transform : register(b0)
{
	matrix g_world;
	matrix g_view;
	matrix g_projection;
	matrix g_WVP;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

PS_OUTPUT_SINGLE_TARGET BasicTexPS(VS_OUTPUT_POSITION_TEX input)
{
	PS_OUTPUT_SINGLE_TARGET output = (PS_OUTPUT_SINGLE_TARGET)0;

	output.target = g_texture.Sample(g_sampler, input.uv);

	return output;
}