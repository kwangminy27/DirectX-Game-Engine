#include "DGEngine_stdafx.h"
#include "text.h"

#include "device.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/Transform.h"
#include "font_manager.h"

using namespace DG;

void Text::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::TEXT;

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Text::Initialize" << std::endl;
	}
}

std::wstring const& Text::text() const
{
	return text_;
}

DWRITE_TEXT_ALIGNMENT Text::text_alignment() const
{
	return text_alignment_;
}

DWRITE_PARAGRAPH_ALIGNMENT Text::paragraph_alignment() const
{
	return paragraph_alignment_;
}

bool Text::ui_flag() const
{
	return ui_flag_;
}

bool Text::shadow_flag() const
{
	return shadow_flag_;
}

bool Text::shadow_alpha_flag() const
{
	return shadow_alpha_flag_;
}

float Text::shadow_opacity() const
{
	return shadow_opacity_;
}

Math::Vector3 const& Text::shadow_offset() const
{
	return shadow_offset_;
}

std::string const& Text::text_format_tag() const
{
	return text_format_tag_;
}

std::string const& Text::text_layout_tag() const
{
	return text_layout_tag_;
}

Math::Vector4 const& Text::brush_color() const
{
	return brush_color_;
}

Math::Vector4 const& Text::shadow_brush_color() const
{
	return shadow_brush_color_;
}

D2D1_RECT_F Text::text_area() const
{
	return text_area_;
}

void Text::set_text(std::wstring const& _text)
{
	text_ = _text;
}

void Text::set_text_alignment(DWRITE_TEXT_ALIGNMENT _alignment)
{
	text_alignment_ = _alignment;
}

void Text::set_paragraph_alignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment)
{
	paragraph_alignment_ = _alignment;
}

void Text::set_ui_flag(bool _flag)
{
	ui_flag_ = _flag;
}

void Text::set_shadow_flag(bool _flag)
{
	shadow_flag_ = _flag;
}

void Text::set_shadow_alpha_flag(bool _flag)
{
	shadow_alpha_flag_ = _flag;
}

void Text::set_shadow_opacity(float _opacity)
{
	shadow_opacity_ = _opacity;
}

void Text::set_shadow_offset(Math::Vector3 const& _offset)
{
	shadow_offset_ = _offset;
}

void Text::set_text_format_tag(std::string const& _tag)
{
	text_format_tag_ = _tag;
}

void Text::set_text_layout_tag(std::string const& _tag)
{
	text_layout_tag_ = _tag;
}

void Text::set_brush_color(Math::Vector4 const& _color)
{
	brush_color_ = _color;
}

void Text::set_shadow_brush_color(Math::Vector4 const& _color)
{
	shadow_brush_color_ = _color;
}

void Text::set_text_area(D2D1_RECT_F _area)
{
	text_area_ = _area;
}

Text::Text(Text const& _other) : Component(_other)
{
	text_ = _other.text_;
	ui_flag_ = _other.ui_flag_;
	shadow_flag_ = _other.shadow_flag_;
	shadow_alpha_flag_ = _other.shadow_alpha_flag_;
	shadow_opacity_ = _other.shadow_opacity_;
	shadow_offset_ = _other.shadow_offset_;
	text_layout_tag_ = _other.text_layout_tag_;
	shadow_brush_color_ = _other.shadow_brush_color_;
	brush_color_ = _other.brush_color_;
	text_area_ = _other.text_area_;
}

Text::Text(Text&& _other) noexcept : Component(std::move(_other))
{
	text_ = std::move(_other.text_);
	ui_flag_ = std::move(_other.ui_flag_);
	shadow_flag_ = std::move(_other.shadow_flag_);
	shadow_alpha_flag_ = std::move(_other.shadow_alpha_flag_);
	shadow_opacity_ = std::move(_other.shadow_opacity_);
	shadow_offset_ = std::move(_other.shadow_offset_);
	text_layout_tag_ = std::move(_other.text_layout_tag_);
	shadow_brush_color_ = std::move(_other.shadow_brush_color_);
	brush_color_ = std::move(_other.brush_color_);
	text_area_ = std::move(_other.text_area_);
}

void Text::_Release()
{
}

void Text::_Input(float _time)
{
}

void Text::_Update(float _time)
{
}

void Text::_LateUpdate(float _time)
{
}

void Text::_Collision(float _time)
{
}

void Text::_Render(float _time)
{
	// DrawTextLayout, DrawText 둘 다 지원.

	auto const& font_manager = FontManager::singleton();
	auto const& d2d_render_target = Device::singleton()->d2d_render_target();

	auto const& text_format = font_manager->FindTextFormat(text_format_tag_);
	auto const& text_layout = font_manager->FindTextLayout(text_layout_tag_);
	auto const& brush = font_manager->FindSolidColorBrush(brush_color_);
	auto const& shadow_brush = font_manager->FindSolidColorBrush(shadow_brush_color_);

	auto position = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM))->GetWorldPosition();

	d2d_render_target->BeginDraw();

	text_format->SetTextAlignment(text_alignment_);
	text_format->SetParagraphAlignment(paragraph_alignment_);

	if (text_layout)
	{
		text_layout->SetTextAlignment(text_alignment_);
		text_layout->SetParagraphAlignment(paragraph_alignment_);

		if (!ui_flag_)
		{
			auto const& camera_transform = std::dynamic_pointer_cast<Transform>(scene()->main_camera()->FindComponent(COMPONENT_TYPE::TRANSFORM));

			position -= camera_transform->GetWorldPosition();
		}

		if (shadow_flag_)
		{
			auto shadow_position = position + shadow_offset_;

			if (shadow_alpha_flag_)
				shadow_brush->SetOpacity(shadow_opacity_);
			else
				shadow_brush->SetOpacity(1.f);

			shadow_position.y = static_cast<float>(RESOLUTION::HEIGHT) - shadow_position.y;

			d2d_render_target->DrawTextLayout(
				D2D1::Point2F(shadow_position.x, shadow_position.y),
				text_layout.Get(),
				shadow_brush.Get()
			);
		}

		position.y = static_cast<float>(RESOLUTION::HEIGHT) - position.y;

		d2d_render_target->DrawTextLayout(
			D2D1::Point2F(position.x, position.y),
			text_layout.Get(),
			brush.Get()
		);
	}
	else
	{ // text_layout이 없는 경우
		auto render_area = text_area_;
		auto shadow_render_area = text_area_;

		if (!ui_flag_)
		{
			auto const& camera_transform = std::dynamic_pointer_cast<Transform>(scene()->main_camera()->FindComponent(COMPONENT_TYPE::TRANSFORM));

			position -= camera_transform->GetWorldPosition();
		}

		if (shadow_flag_)
		{
			auto shadow_position = position + shadow_offset_;

			if (shadow_alpha_flag_)
				shadow_brush->SetOpacity(shadow_opacity_);
			else
				shadow_brush->SetOpacity(1.f);

			shadow_render_area.left += shadow_position.x;
			shadow_render_area.right += shadow_position.x;
			shadow_render_area.top += static_cast<float>(RESOLUTION::HEIGHT) - shadow_position.y;
			shadow_render_area.bottom += static_cast<float>(RESOLUTION::HEIGHT) - shadow_position.y;

			d2d_render_target->DrawTextW(
				text_.c_str(),
				static_cast<uint32_t>(text_.length()),
				text_format.Get(),
				shadow_render_area,
				shadow_brush.Get()
			);
		}

		render_area.left += position.x;
		render_area.right += position.x;
		render_area.top += static_cast<float>(RESOLUTION::HEIGHT) - position.y;
		render_area.bottom += static_cast<float>(RESOLUTION::HEIGHT) - position.y;

		d2d_render_target->DrawTextW(
			text_.c_str(),
			static_cast<uint32_t>(text_.length()),
			text_format.Get(),
			render_area,
			brush.Get()
		);
	}

	d2d_render_target->EndDraw();
}

std::unique_ptr<Component, std::function<void(Component*)>> Text::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Text{ *this }, [](Component* _p) {
		dynamic_cast<Text*>(_p)->_Release();
		delete dynamic_cast<Text*>(_p);
	} };
}

void Text::_AfterClone()
{
}
