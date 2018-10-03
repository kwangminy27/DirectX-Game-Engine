#pragma once

#include "tag.h"

namespace DG
{
	class SceneComponent;
	class Layer;
	class Object;
	class Camera;

	class DG_ENGINE_DLL Scene final : public Tag, public std::enable_shared_from_this<Scene>
	{
		friend class SceneManager;
	public:
		std::shared_ptr<SceneComponent> const& FindSceneComponent(std::string const& _tag) const;
		std::shared_ptr<Layer> const& FindLayer(std::string const& _tag) const;
		std::shared_ptr<Object> const& FindObject(std::string const& _tag) const;
		std::shared_ptr<Object> const& FindCamera(std::string const& _tag) const;

		std::shared_ptr<Object> const& main_camera() const;

	private:
		Scene() = default;
		Scene(Scene const& _other);
		Scene(Scene&& _other) noexcept;
		Scene& operator=(Scene const&) = default;
		Scene& operator=(Scene&&) noexcept = default;

		virtual void _Release() override;

		template <typename T> void _AddSceneComponent(std::string const& _tag);
		void _AddLayer(std::string const& _tag, int _z_order);

		void _Initialize();
		void _Input(float _time);
		void _Update(float _time);
		void _LateUpdate(float _time);
		void _Collision(float _time);
		void _Render(float _time);

		std::shared_ptr<Object> _CreateCamera(
			std::string const& _tag,
			Math::Vector3 const& _position,
			CAMERA_TYPE _type,
			float _fov_angle,
			float _width,
			float _height,
			float _near,
			float _far);
		void _ChangeCamera(std::string const& _tag);

		static std::shared_ptr<SceneComponent> scene_component_nullptr_;
		static std::shared_ptr<Layer> layer_nullptr_;
		static std::shared_ptr<Object> camera_nullptr_;
		std::list<std::shared_ptr<SceneComponent>> scene_component_list_{};
		std::list<std::shared_ptr<Layer>> layer_list_{};
		std::unordered_map<std::string, std::shared_ptr<Object>> camera_map_{};
		std::shared_ptr<Object> main_camera_{};
	};
}

#include "scene.inl"