#pragma once

#include <DGMath_stdafx.h>
#include <DGMath.h>

namespace DG
{
	struct VertexColor
	{
		Math::Vector3 position;
		Math::Vector4 color;
	};

	struct VertexTex
	{
		Math::Vector3 position;
		Math::Vector2 UV;
	};

	struct ConstantBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		int size;
		int shader_type;
		int slot;
	};

	struct TransformConstantBuffer
	{
		Math::Matrix world;
		Math::Matrix view;
		Math::Matrix projection;
		Math::Matrix WVP;
		Math::Vector3 pivot;
		float empty;
		Math::Vector3 diagonal;
		float empty1; // packed_offset 사용해서 마지막에만 패딩 해보자.
	};

	struct MaterialConstantBuffer
	{
		Math::Vector4 diffuse;
	};
}