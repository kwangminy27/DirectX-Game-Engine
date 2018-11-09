#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Text final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		std::wstring const& text() const;
		DWRITE_TEXT_ALIGNMENT text_alignment() const;
		DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment() const;
		bool ui_flag() const;
		bool shadow_flag() const;
		bool shadow_alpha_flag() const;
		float shadow_opacity() const;
		Math::Vector3 const& shadow_offset() const;
		std::string const& text_format_tag() const;
		std::string const& text_layout_tag() const;
		Math::Vector4 const& brush_color() const;
		Math::Vector4 const& shadow_brush_color() const;
		D2D1_RECT_F text_area() const;

		void set_text(std::wstring const& _text);
		void set_text_alignment(DWRITE_TEXT_ALIGNMENT _alignment);
		void set_paragraph_alignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment);
		void set_ui_flag(bool _flag);
		void set_shadow_flag(bool _flag);
		void set_shadow_alpha_flag(bool _flag);
		void set_shadow_opacity(float _opacity);
		void set_shadow_offset(Math::Vector3 const& _offset);
		void set_text_format_tag(std::string const& _tag);
		void set_text_layout_tag(std::string const& _tag);
		void set_brush_color(Math::Vector4 const& _color);
		void set_shadow_brush_color(Math::Vector4 const& _color);
		void set_text_area(D2D1_RECT_F _area); // 순서대로 left, bottom, right, top

	private:
		Text() = default;
		Text(Text const& _other);
		Text(Text&& _other) noexcept;
		Text& operator=(Text const&) = default;
		Text& operator=(Text&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		std::wstring text_{};
		DWRITE_TEXT_ALIGNMENT text_alignment_{};
		DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment_{};
		bool ui_flag_{};
		bool shadow_flag_{};
		bool shadow_alpha_flag_{};
		float shadow_opacity_{};
		Math::Vector3 shadow_offset_{};
		std::string text_format_tag_{};
		std::string text_layout_tag_{};
		Math::Vector4 brush_color_{};
		Math::Vector4 shadow_brush_color_{};
		D2D1_RECT_F text_area_{};
	};
}
