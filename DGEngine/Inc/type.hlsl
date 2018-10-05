struct VS_INPUT_POSITION_COLOR
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_INPUT_POSITION_TEX
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT_POSITION_COLOR
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT_POSITION_TEX
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
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
	float3 g_pivot;
	float empty;
	float3 g_diagonal;
	float empty1;
}

cbuffer Material : register(b1)
{
	float4 g_diffuse;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
