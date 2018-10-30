#pragma once

#include "UI.h"

namespace DG
{
	class DG_ENGINE_DLL BarUI : public UI
	{
		friend class Object;
	public:
		virtual void Initialize() override;
		virtual void UpdateConstantBuffer();

		void AddValue(float _time);

		void set_direction(CUTTING_DIR _direction);
		void set_range(float _min, float _max);
		void set_value(float _value);

	protected:
		BarUI() = default;
		BarUI(BarUI const& _other);
		BarUI(BarUI&& _other) noexcept;
		BarUI& operator=(BarUI const&) = default;
		BarUI& operator=(BarUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		CUTTING_DIR direction_{};
		std::pair<float, float> range_{};
		float value_{};
	};
}
