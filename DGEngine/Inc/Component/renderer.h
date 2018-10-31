#pragma once

#include "component.h"

namespace DG
{
	class Mesh;
	class Shader;
	class RenderState;

	class DG_ENGINE_DLL Renderer final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void set_mesh_tag(std::string const& _tag);
		void set_shader_tag(std::string const& _tag);
		void set_render_state(std::string const& _tag);

	private:
		Renderer() = default;
		Renderer(Renderer const& _other);
		Renderer(Renderer&& _other) noexcept;
		Renderer& operator=(Renderer const&) = default;
		Renderer& operator=(Renderer&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		void _UpdateConstantBuffers(float _time);
		void _UpdateTransform();

		std::string mesh_tag_{};
		std::string shader_tag_{};
		std::array<std::shared_ptr<RenderState>, static_cast<int>(RENDER_STATE_TYPE::END)> render_state_array_{};
	};
}
