struct VS_INPUT_POSITION_TEX_INSTANCE
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float4x4 world : WORLD;
};

struct VS_OUTPUT_POSITION_TEX
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
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

VS_OUTPUT_POSITION_TEX InstanceTexVS(VS_INPUT_POSITION_TEX_INSTANCE input)
{
	VS_OUTPUT_POSITION_TEX output = (VS_OUTPUT_POSITION_TEX)0;

	float3 position = input.position - g_diagonal * g_pivot;

	output.position = mul(mul(mul(float4(position, 1), input.world), g_view), g_projection);
	output.uv = input.uv;

	return output;
}