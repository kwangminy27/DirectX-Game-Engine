#pragma once

#include "tag.h"

namespace DG
{
	class Scene;
	class Layer;
	class Component;

	class DG_ENGINE_DLL Object final : public Tag, public std::enable_shared_from_this<Object>
	{
		friend class SceneManager;
		friend class Scene;
		friend class Layer;
		friend class InputManager;
	public:
		static std::shared_ptr<Object> CreatePrototype(std::string const& _tag, bool _next_scene_flag);
		static std::shared_ptr<Object> CreateClone(std::string const& _tag, std::string const& _prototype_tag, std::shared_ptr<Layer> const& _layer, bool _next_scene_flag);
		static std::shared_ptr<Object> CreateObject(std::string const& _tag, std::shared_ptr<Layer> const& _layer); // child 만들 때는 layer를 nullptr로 설정
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

		void AfterClone();
		void Test(std::shared_ptr<Scene> const& _scene, std::shared_ptr<Layer> const& _layer, std::shared_ptr<Object> const& _object);

		std::shared_ptr<Scene> scene() const;
		std::shared_ptr<Layer> layer() const;

		void set_scene(std::shared_ptr<Scene> const& _scene);
		void set_layer(std::shared_ptr<Layer> const& _layer);
		void AddChild(std::shared_ptr<Object> const& _child); // Child Object 만들자마자 부모에 추가해줘야 함. 그래야 나중에 추가하는 Component들에도 scene, layer가 정상적으로 들어감

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
		std::list<std::weak_ptr<Object>> child_list_{}; // layer에 추가하는 방식으로 구현
	};
}

#include "object.inl"
