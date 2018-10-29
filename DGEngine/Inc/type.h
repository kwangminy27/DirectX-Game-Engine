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

	struct Animation2DConstantBuffer
	{
		Math::Vector2 UVLT;
		Math::Vector2 UVRB;
		int frame_idx; // used only for texture array.
		Math::Vector3 empty;
	};

	struct Animation2DFrameDesc
	{
		Math::Vector2 LT;
		Math::Vector2 RB;
	};

	struct Animation2DClipDesc
	{
		ANIMATION_2D_TYPE type;
		ANIMATION_OPTION option;
		std::string animation_tag;
		std::string texture_tag;
		float width;
		float height;
		std::vector<Animation2DFrameDesc> frame_vector;
		float completion_time;
	};

	struct RectInfo
	{
		Math::Vector3 min;
		Math::Vector3 max;
		Math::Vector3 diagonal;
	};

	struct CircleInfo
	{
		Math::Vector3 center;
		float radius;
	};

	struct OOBBInfo
	{
		Math::Vector3 center;
		Math::Vector3 extent;
		Math::Matrix rotation;
	};

	struct Pixel24
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	struct _PixelInfo
	{
		Pixel24* pixel_collection;
		int width;
		int height;
	};

	struct PixelInfo
	{
		std::string tag;
		RectInfo rect_info;
		Pixel24 nodal_point;
	};
}