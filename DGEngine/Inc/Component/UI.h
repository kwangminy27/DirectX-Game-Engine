#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL UI : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		UI_TYPE ui_type() const;
		void set_ui_type(UI_TYPE _type);

	protected:
		UI() = default;
		UI(UI const& _other);
		UI(UI&& _other) noexcept;
		UI& operator=(UI const&) = default;
		UI& operator=(UI&&) noexcept = default;
		virtual ~UI() = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		UI_TYPE ui_type_{};
	};
}
