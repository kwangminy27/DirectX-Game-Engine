struct VS_INPUT_POS
{
	float3 position : POSITION;
};

struct VS_INPUT_POSITION_COLOR
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_INPUT_POSITION_TEX
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT_POS
{
	float4 position : SV_POSITION;
};

struct VS_OUTPUT_POSITION_COLOR
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

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
	float3 g_pivot;
	float empty;
	float3 g_diagonal;
	float empty1;
}

cbuffer Material : register(b1)
{
	float4 g_diffuse;
}

cbuffer Animation2D : register(b8)
{
	float2 g_UVLT;
	float2 g_UVRB;
	int g_frame_idx;
	float3 empty2;
};

cbuffer Collider : register(b9)
{
	float4 g_color;
}

cbuffer Button : register(b10)
{
	float4 g_color;
	int g_checkbox_state;
	float3 empty3;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
