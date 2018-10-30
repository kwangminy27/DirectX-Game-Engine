#pragma once

#include "tag.h"

namespace DG
{
	class Scene;
	class Layer;
	class Object;

	class DG_ENGINE_DLL Component : public Tag
	{
		friend class Object;
	public:
		virtual void Initialize() = 0;

		COMPONENT_TYPE type() const;
		std::string const& object_tag() const;
		std::shared_ptr<Scene> scene() const;
		std::shared_ptr<Layer> layer() const;
		std::shared_ptr<Object> object() const;

		void set_type(COMPONENT_TYPE _type);
		void set_object_tag(std::string const& _tag);
		void set_scene(std::shared_ptr<Scene> const& _scene);
		void set_layer(std::shared_ptr<Layer> const& _layer);
		void set_object(std::shared_ptr<Object> const& _object);

	protected:
		Component() = default;
		Component(Component const& _other);
		Component(Component&& _other) noexcept;
		Component& operator=(Component const&) = default;
		Component& operator=(Component&&) noexcept = default;
		virtual ~Component() = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const = 0;
		virtual void _AfterClone();

		COMPONENT_TYPE type_{};
		std::string object_tag_{};
		std::weak_ptr<Scene> scene_{};
		std::weak_ptr<Layer> layer_{};
		std::weak_ptr<Object> object_{};
	};
}
