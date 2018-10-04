#pragma once

#include "component.h"

namespace DG
{
	class Mesh;
	class Shader;
	class Material;

	class DG_ENGINE_DLL Renderer final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void set_mesh(std::string const& _tag);
		void set_mesh(std::shared_ptr<Mesh> const& _mesh);
		void set_shader(std::string const& _tag);
		void set_shader(std::shared_ptr<Shader> const& _shader);

	private:
		Renderer() = default;
		Renderer(Renderer const& _other);
		Renderer(Renderer&& _other) noexcept;
		Renderer& operator=(Renderer const&) = default;
		Renderer& operator=(Renderer&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		void _UpdateTransform();

		std::shared_ptr<Mesh> mesh_{};
		std::shared_ptr<Shader> shader_{};
		std::shared_ptr<Material> material_{};
	};
}
