struct VS_INPUT_POS
{
	float3 position : POSITION;
};

struct VS_OUTPUT_POS
{
	float4 position : SV_POSITION;
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

VS_OUTPUT_POS ColliderVS(VS_INPUT_POS input)
{
	VS_OUTPUT_POS output = (VS_OUTPUT_POS)0;

	output.position = mul(float4(input.position, 1.f), g_WVP);

	return output;
}