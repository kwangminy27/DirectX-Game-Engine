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

VS_OUTPUT_POSITION_COLOR BasicVS(VS_INPUT_POSITION_COLOR input)
{
	VS_OUTPUT_POSITION_COLOR output = (VS_OUTPUT_POSITION_COLOR)0;

	output.position = float4(input.position, 1.f);
	output.color = input.color;

	return output;
}