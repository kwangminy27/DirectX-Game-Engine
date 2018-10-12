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

VS_OUTPUT_POSITION_TEX BasicAnimation2DVS(VS_INPUT_POSITION_TEX input)
{
	VS_OUTPUT_POSITION_TEX output = (VS_OUTPUT_POSITION_TEX)0;

	float3 position = input.position - g_diagonal * g_pivot;

	output.position = mul(float4(position, 1.f), g_WVP);

	if (input.uv.x == 0.f)
		output.uv.x = g_UVLT.x;
	else
		output.uv.x = g_UVRB.x;

	if (input.uv.y == 0.f)
		output.uv.y = g_UVLT.y;
	else
		output.uv.y = g_UVRB.y;

	return output;
}