#pragma once

#include <DGEngine_stdafx.h>
#include <Component/user_component.h>

namespace DG
{
	class PlayerComponent final : public UserComponent
	{
		friend class Object;
	public:
		virtual void Initialize() override;

	private:
		PlayerComponent() = default;
		PlayerComponent(PlayerComponent const& _other);
		PlayerComponent(PlayerComponent&& _other) noexcept;
		PlayerComponent& operator=(PlayerComponent const&) = default;
		PlayerComponent& operator=(PlayerComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
	};
}
