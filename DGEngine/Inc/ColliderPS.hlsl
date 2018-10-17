struct VS_OUTPUT_POS
{
	float4 position : SV_POSITION;
};

struct PS_OUTPUT_SINGLE_TARGET
{
	float4 target : SV_TARGET;
};

cbuffer Collider : register(b8)
{
	float4 g_color;
}

PS_OUTPUT_SINGLE_TARGET ColliderPS(VS_OUTPUT_POS input)
{
	PS_OUTPUT_SINGLE_TARGET output = (PS_OUTPUT_SINGLE_TARGET)0;

	output.target = g_color;

	return output;
}