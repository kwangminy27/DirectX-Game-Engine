#include "DGEngine_stdafx.h"
#include "UI.h"

using namespace DG;

void UI::Initialize()
{
	type_ = COMPONENT_TYPE::UI;
}

UI_TYPE UI::ui_type() const
{
	return ui_type_;
}

void UI::set_ui_type(UI_TYPE _type)
{
	ui_type_ = _type;
}

UI::UI(UI const& _other) : Component(_other)
{
	ui_type_ = _other.ui_type_;
}

UI::UI(UI&& _other) noexcept
{
	ui_type_ = std::move(_other.ui_type_);
}

void UI::_Release()
{
}

void UI::_Input(float _time)
{
}

void UI::_Update(float _time)
{
}

void UI::_LateUpdate(float _time)
{
}

void UI::_Collision(float _time)
{
}

void UI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> UI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new UI{ *this }, [](Component* _p) {
		dynamic_cast<UI*>(_p)->_Release();
		delete dynamic_cast<UI*>(_p);
	} };
}

void UI::_AfterClone()
{
}
