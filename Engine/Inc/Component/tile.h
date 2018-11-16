#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Tile final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		TILE_OPTION tile_option() const;

		void set_tile_option(TILE_OPTION _option);

	protected:
		Tile() = default;
		Tile(Tile const& _other);
		Tile(Tile&& _other) noexcept;
		Tile& operator=(Tile const&) = default;
		Tile& operator=(Tile&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		TILE_OPTION tile_option_{};
	};
}
