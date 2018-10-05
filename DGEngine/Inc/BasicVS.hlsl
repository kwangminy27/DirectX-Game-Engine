struct VS_INPUT_POSITION_COLOR
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT_POSITION_COLOR
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
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

VS_OUTPUT_POSITION_COLOR BasicVS(VS_INPUT_POSITION_COLOR input)
{
	VS_OUTPUT_POSITION_COLOR output = (VS_OUTPUT_POSITION_COLOR)0;

	float3 position = input.position - g_diagonal * g_pivot;

	output.position = mul(float4(position, 1.f), g_WVP);
	output.color = input.color;

	return output;
}