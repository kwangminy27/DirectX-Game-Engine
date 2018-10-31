#include "DGEngine_stdafx.h"
#include "bar_UI.h"

#include "object.h"
#include "Component/transform.h"

using namespace DG;

void BarUI::Initialize()
{
	try
	{
		UI::Initialize();

		set_direction(CUTTING_DIR::RIGHT_TO_LEFT);
		set_range(0.f, 100.f);
		set_value(100.f);
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "BarUI::Initialize()" << std::endl;
	}
}

void BarUI::UpdateConstantBuffer()
{
}

void BarUI::AddValue(float _time)
{
	value_ += _time;
}

void BarUI::set_direction(CUTTING_DIR _direction)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	direction_ = _direction;

	switch (_direction)
	{
	case CUTTING_DIR::BOTTOM_TO_TOP:
		transform->set_pivot({ 0.f, 1.f, 0.f });
		transform->Translation({ 0.f, transform->GetLocalScale().y, 0.f });
		break;
	case CUTTING_DIR::LEFT_TO_RIGHT:
		transform->set_pivot({ 1.f, 0.f, 0.f });
		transform->Translation({ transform->GetLocalScale().x, 0.f, 0.f });
		break;
	case CUTTING_DIR::RIGHT_TO_LEFT:
		transform->set_pivot({ 0.f, 0.f, 0.f });
		break;
	case CUTTING_DIR::TOP_TO_BOTTOM:
		transform->set_pivot({ 0.f, 0.f, 0.f });
		break;
	}
}

void BarUI::set_range(float _min, float _max)
{
	range_.first = _min;
	range_.second = _max;

	value_ = std::clamp(value_, _min, _max);
}

void BarUI::set_value(float _value)
{
	value_ = std::clamp(_value, range_.first, range_.second);
}

BarUI::BarUI(BarUI const& _other) : UI(_other)
{
	direction_ = _other.direction_;
	range_ = _other.range_;
	value_ = _other.value_;
}

BarUI::BarUI(BarUI&& _other) noexcept : UI(std::move(_other))
{
	direction_ = std::move(_other.direction_);
	range_ = std::move(_other.range_);
	value_ = std::move(_other.value_);
}

void BarUI::_Release()
{
}

void BarUI::_Input(float _time)
{
}

void BarUI::_Update(float _time)
{
}

void BarUI::_LateUpdate(float _time)
{
}

void BarUI::_Collision(float _time)
{
}

void BarUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> BarUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new BarUI{ *this }, [](Component* _p) {
		dynamic_cast<BarUI*>(_p)->_Release();
		delete dynamic_cast<BarUI*>(_p);
	} };
}

void BarUI::_AfterClone()
{
}
