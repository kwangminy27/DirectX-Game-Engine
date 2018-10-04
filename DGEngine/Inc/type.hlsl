struct VS_INPUT_POSITION_COLOR
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_INPUT_POSITION_TEX
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT_POSITION_COLOR
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT_POSITION_TEX
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

struct PS_OUTPUT_SINGLE_TARGET
{
	float4 target : SV_TARGET;
};