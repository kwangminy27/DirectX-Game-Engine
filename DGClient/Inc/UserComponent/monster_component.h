#pragma once

#include <DGEngine_stdafx.h>
#include <Component/user_component.h>

namespace DG
{
	class Object;

	class MonsterComponent final : public UserComponent
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		std::shared_ptr<Object> target();

		void set_target(std::shared_ptr<Object> const& _target);

	private:
		MonsterComponent() = default;
		MonsterComponent(MonsterComponent const& _other);
		MonsterComponent(MonsterComponent&& _other) noexcept;
		MonsterComponent& operator=(MonsterComponent const&) = default;
		MonsterComponent& operator=(MonsterComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		std::weak_ptr<Object> target_{};
	};
}
