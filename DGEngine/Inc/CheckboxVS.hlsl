struct VS_INPUT_POSITION_TEX
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
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

VS_OUTPUT_POSITION_TEX CheckboxVS(VS_INPUT_POSITION_TEX input)
{
	VS_OUTPUT_POSITION_TEX output = (VS_OUTPUT_POSITION_TEX)0;

	float3 position = input.position - g_diagonal * g_pivot;

	output.position = mul(float4(position, 1.f), g_WVP);
	output.uv = input.uv;

	return output;
}