#pragma once

#include "tag.h"

namespace DG
{
	class Scene;
	class Layer;
	class Component;

	class DG_ENGINE_DLL Object final : public Tag, public std::enable_shared_from_this<Object>
	{
		friend class Scene;
		friend class Layer;
		friend class InputManager;
	public:
		static std::shared_ptr<Object> CreatePrototype(std::string const& _tag, bool _current_flag);
		static std::shared_ptr<Object> CreateClone(std::string const& _tag, std::string const& _prototype_tag, std::shared_ptr<Layer> const& _layer, bool _current_flag);
		static std::shared_ptr<Object> CreateObject(std::string const& _tag, std::shared_ptr<Layer> const& _layer);
		static std::shared_ptr<Object> FindPrototype(std::string const& _scene_tag, std::string const& _tag);
		static std::shared_ptr<Object> FindObject(std::string const& _tag);
		static void DestroyPrototype();
		static void DestroyPrototype(std::string const& _scene_tag);
		static void DestroyPrototype(std::string const& _scene_tag, std::string const& _tag);

		template <typename T> std::shared_ptr<Component> AddComponent(std::string const& _tag);
		std::shared_ptr<Component> const& FindComponent(std::string const& _tag) const;
		std::shared_ptr<Component> const& FindComponent(COMPONENT_TYPE _type) const;
		std::list<std::shared_ptr<Component>> const& FindComponents(COMPONENT_TYPE _type) const;
		bool IsComponent(COMPONENT_TYPE _type) const;

		void Test(std::shared_ptr<Scene> const& _scene, std::shared_ptr<Layer> const& _layer, std::shared_ptr<Object> const& _object);

		std::shared_ptr<Scene> scene() const;
		std::shared_ptr<Layer> layer() const;

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

		static std::shared_ptr<Component> component_nullptr_;
		static std::shared_ptr<Object> prototype_nullptr_;
		static std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Object>>> prototype_map_;
		std::weak_ptr<Scene> scene_{};
		std::weak_ptr<Layer> layer_{};
		std::list<std::shared_ptr<Component>> component_list_{};
	};
}

#include "object.inl"
