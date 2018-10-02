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
}

VS_OUTPUT_POSITION_COLOR BasicVS(VS_INPUT_POSITION_COLOR input)
{
	VS_OUTPUT_POSITION_COLOR output = (VS_OUTPUT_POSITION_COLOR)0;

	output.position = mul(float4(input.position, 1.f), g_WVP);
	output.color = input.color;

	return output;
}