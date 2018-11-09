#include "DGEngine_stdafx.h"
#include "font_manager.h"

#include "device.h"

using namespace DG;

using Microsoft::WRL::ComPtr;

ComPtr<IDWriteTextFormat> FontManager::text_format_nullptr_{};
ComPtr<IDWriteTextLayout> FontManager::text_layout_nullptr_{};
ComPtr<ID2D1SolidColorBrush> FontManager::solid_color_brush_nullptr_{};

void FontManager::Initialize()
{
	try
	{
		ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &dwrite_factory_));

		CreateTextFormat("�Ϲ�", L"�ü�ü", DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.f, L"ko");

		CreateSolidColorBrush(DirectX::Colors::Red.v);
		CreateSolidColorBrush(DirectX::Colors::Green.v);
		CreateSolidColorBrush(DirectX::Colors::Blue.v);
		CreateSolidColorBrush(DirectX::Colors::Gold.v);
		CreateSolidColorBrush(DirectX::Colors::Black.v);
		CreateSolidColorBrush(DirectX::Colors::White.v);
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "FontManager::Initialize" << std::endl;
	}
}

ComPtr<IDWriteTextFormat> const& FontManager::FindTextFormat(std::string const& _tag) const
{
	auto iter = text_format_map_.find(_tag);

	if (iter == text_format_map_.end())
		return text_format_nullptr_;

	return iter->second;
}

ComPtr<IDWriteTextLayout> const& FontManager::FindTextLayout(std::string const& _tag) const
{
	auto iter = text_layout_map_.find(_tag);

	if (iter == text_layout_map_.end())
		return text_layout_nullptr_;

	return iter->second;
}

ComPtr<ID2D1SolidColorBrush> const& FontManager::FindSolidColorBrush(Math::Vector4 const& _color) const
{
	auto key = CreateColorKey(_color);

	auto iter = solid_color_brush_map_.find(key);

	if (iter == solid_color_brush_map_.end())
		return solid_color_brush_nullptr_;

	return iter->second;
}

ComPtr<IDWriteTextFormat> FontManager::CreateTextFormat(
	std::string const& _tag,
	std::wstring const& _font_family_name,
	DWRITE_FONT_WEIGHT _weight,
	DWRITE_FONT_STYLE _style,
	DWRITE_FONT_STRETCH _stretch,
	float _size,
	std::wstring const& _locale_name)
{
	// Text Format�� �����Ѵ�.
	// 1������ : ��Ʈ �̸��� �Է��Ѵ�. 
	// 2������ : Ư�� ��Ʈ�� �÷����� ������ �ִ�. �� Arial �� Arial Black �̷���
	// 3������ : ��Ʈ ����
	// 4������ : ����
	// 5������ : �ڰ�
	// 6������ : ��Ʈ ũ��
	// 7������ : ��� ���� �̸��� �����Ѵ�. �ѱ��� ko - KR �̱��� en - us 
	// 8������ : �ؽ�Ʈ �������̽�

	auto text_format = FindTextFormat(_tag);;

	if (text_format)
		throw std::exception{ "FontManager::CreateTextFormat" };

	ThrowIfFailed(dwrite_factory_->CreateTextFormat(
		_font_family_name.c_str(),
		nullptr,
		_weight,
		_style,
		_stretch,
		_size,
		_locale_name.c_str(),
		&text_format
	));

	text_format_map_.insert(make_pair(_tag, text_format));

	return text_format;
}

ComPtr<IDWriteTextLayout> FontManager::CreateTextLayout(
	std::string const& _tag,
	std::wstring const& _text,
	std::string const& _text_format_tag,
	float _max_width,
	float _max_height)
{
	ComPtr<IDWriteTextLayout> text_layout = FindTextLayout(_tag);

	if (text_layout)
		throw std::exception{ "FontManager::CreateTextLayout" };

	auto const& text_format = FindTextFormat(_text_format_tag);

	if (!text_format)
		throw std::exception{ "FontManager::CreateTextLayout" };

	ThrowIfFailed(dwrite_factory_->CreateTextLayout(
		_text.c_str(),
		static_cast<uint32_t>(_text.length()),
		text_format.Get(),
		_max_width,
		_max_height,
		&text_layout));

	text_layout_map_.insert(make_pair(_tag, text_layout));

	return text_layout;
}

ComPtr<ID2D1SolidColorBrush> FontManager::CreateSolidColorBrush(Math::Vector4 const& _color)
{
	auto solid_color_brush = FindSolidColorBrush(_color);

	if (solid_color_brush)
		throw std::exception{ "FontManager::CreateSolidColorBrush" };

	ThrowIfFailed(Device::singleton()->d2d_render_target()->CreateSolidColorBrush(D2D1::ColorF{ _color.x, _color.y, _color.z, _color.w }, &solid_color_brush));

	auto key = CreateColorKey(_color);

	solid_color_brush_map_.insert(make_pair(key, solid_color_brush));

	return solid_color_brush;
}

unsigned int FontManager::CreateColorKey(Math::Vector4 const& _color) const
{
	auto color = _color;
	color *= 255.f;

	unsigned int key{};
	key |= static_cast<unsigned char>(color.x);
	key |= static_cast<unsigned char>(color.y) << 8;
	key |= static_cast<unsigned char>(color.z) << 16;
	key |= static_cast<unsigned char>(color.w) << 24;

	return key;
}

void FontManager::_Release()
{
}
