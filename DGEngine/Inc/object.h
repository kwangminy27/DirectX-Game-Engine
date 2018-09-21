#pragma once

#include "tag.h"

namespace DG
{
	class Scene;
	class Layer;
	class Component;
	class Transform;

	class Object final : public Tag, public std::enable_shared_from_this<Object>
	{
		friend class Layer;
	public:
		std::shared_ptr<Scene> scene() const;
		std::shared_ptr<Layer> layer() const;
		std::shared_ptr<Transform> transform() const;

		void set_scene(std::shared_ptr<Scene> const& _scene);
		void set_layer(std::shared_ptr<Layer> const& _layer);

	private:
		Object() = default;
		Object(Object const& _other);
		Object(Object&& _other) noexcept;
		Object& operator=(Object const&) = default;
		Object& operator=(Object&&) noexcept = default;

		virtual void _Release() override;

		void _Initialize();
		void _Input(float _time);
		void _Update(float _time);
		void _LateUpdate(float _time);
		void _Collision(float _time);
		void _Render(float _time);
		std::unique_ptr<Object, std::function<void(Object*)>> Clone();

		std::weak_ptr<Scene> scene_{};
		std::weak_ptr<Layer> layer_{};
		std::shared_ptr<Transform> transform_{};
		std::list<std::shared_ptr<Component>> component_list_{};
	};
}
