#pragma once

#include "singleton.h"

namespace DG
{
	class DG_ENGINE_DLL FontManager final : public Singleton<FontManager>
	{
		friend class Singleton<FontManager>;
	public:
		void Initialize();

		Microsoft::WRL::ComPtr<IDWriteTextFormat> const& FindTextFormat(std::string const& _tag) const;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> const& FindSolidColorBrush(unsigned int _key) const;

		Microsoft::WRL::ComPtr<IDWriteTextFormat> CreateTextFormat(
			std::string const& _tag,
			std::wstring const& _font_family_name,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _size,
			std::wstring const& _locale_name);
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> CreateSolidColorBrush(Math::Vector4 const& _color);
		unsigned int CreateColorKey(Math::Vector4 const& _color);

	private:
		FontManager() = default;
		FontManager(FontManager const&) = delete;
		FontManager(FontManager&&) noexcept = delete;
		FontManager& operator=(FontManager const&) = delete;
		FontManager& operator=(FontManager&&) noexcept = delete;

		virtual void _Release() override;

		static Microsoft::WRL::ComPtr<IDWriteTextFormat> text_format_nullptr_;
		static Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> solid_color_brush_nullptr_;
		Microsoft::WRL::ComPtr<IDWriteFactory> dwrite_factory_{};
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<IDWriteTextFormat>> text_format_map_{};
		std::unordered_map<unsigned int, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>> solid_color_brush_map_{};
	};
}
