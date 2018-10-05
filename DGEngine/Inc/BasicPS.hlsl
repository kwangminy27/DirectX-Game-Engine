struct VS_OUTPUT_POSITION_COLOR
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
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

PS_OUTPUT_SINGLE_TARGET BasicPS(VS_OUTPUT_POSITION_COLOR input)
{
	PS_OUTPUT_SINGLE_TARGET output = (PS_OUTPUT_SINGLE_TARGET)0;

	output.target = input.color;

	return output;
}