#include "DGEngine_stdafx.h"
#include "font_manager.h"

#include "device.h"

using namespace DG;

using Microsoft::WRL::ComPtr;

ComPtr<IDWriteTextFormat> FontManager::text_format_nullptr_{};
ComPtr<ID2D1SolidColorBrush> FontManager::solid_color_brush_nullptr_{};

void FontManager::Initialize()
{
	try
	{
		ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &dwrite_factory_));
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

ComPtr<ID2D1SolidColorBrush> const& FontManager::FindSolidColorBrush(unsigned int _key) const
{
	auto iter = solid_color_brush_map_.find(_key);

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
	// Text Format을 설정한다.
	// 1번인자 : 폰트 이름을 입력한다. 
	// 2번인자 : 특정 폰트는 컬렉션을 가지고 있다. 예 Arial 은 Arial Black 이런식
	// 3번인자 : 폰트 굵기
	// 4번인자 : 기울기
	// 5번인자 : 자간
	// 6번인자 : 폰트 크기
	// 7번인자 : 언어 지역 이름을 설정한다. 한국은 ko - KR 미국은 en - us 
	// 8번인자 : 텍스트 인터페이스

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

ComPtr<ID2D1SolidColorBrush> FontManager::CreateSolidColorBrush(Math::Vector4 const& _color)
{
	auto key = CreateColorKey(_color);

	auto solid_color_brush = FindSolidColorBrush(key);

	if (solid_color_brush)
		throw std::exception{ "FontManager::CreateSolidColorBrush" };

	ThrowIfFailed(Device::singleton()->d2d_render_target()->CreateSolidColorBrush(D2D1::ColorF{ _color.x, _color.y, _color.z, _color.w }, &solid_color_brush));

	solid_color_brush_map_.insert(make_pair(key, solid_color_brush));

	return solid_color_brush;
}

unsigned int FontManager::CreateColorKey(Math::Vector4 const& _color)
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
