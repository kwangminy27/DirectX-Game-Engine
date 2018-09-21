#pragma once

#include "tag.h"

namespace DG
{
	class Scene;

	class Layer final : public Tag
	{
		friend class Scene;
	public:
		int z_order() const;
		std::shared_ptr<Scene> scene() const;

		void set_z_order(int _z_order);
		void set_scene(std::shared_ptr<Scene> const& _scene);

	private:
		Layer() = default;
		Layer(Layer const& _other);
		Layer(Layer&& _other) noexcept;
		Layer& operator=(Layer const&) = default;
		Layer& operator=(Layer&&) noexcept = default;

		virtual void _Release() override;

		void _Initialize();
		void _Input(float _time);
		void _Update(float _time);
		void _LateUpdate(float _time);
		void _Collision(float _time);
		void _Render(float _time);

		int z_order_{};
		std::weak_ptr<Scene> scene_{};
	};
}
