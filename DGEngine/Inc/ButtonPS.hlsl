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

cbuffer Button : register(b10)
{
	float4 g_color;
	int g_checkbox_state;
	float3 empty3;
}

Texture2D g_texture : register(t0);
Texture2D g_texture_2 : register(t1);
SamplerState g_sampler : register(s0);

PS_OUTPUT_SINGLE_TARGET ButtonPS(VS_OUTPUT_POSITION_TEX input)
{
	PS_OUTPUT_SINGLE_TARGET output = (PS_OUTPUT_SINGLE_TARGET)0;
	
	float4 color = g_texture_2.Sample(g_sampler, input.uv);

	output.target = g_texture.Sample(g_sampler, input.uv) * g_diffuse * g_color + float4(color.r, color.r, color.r, 0.f);

	return output;
}