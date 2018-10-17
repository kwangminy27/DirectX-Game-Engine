#include "DGEngine_stdafx.h"
#include "renderer.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "Rendering/render_state.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/material.h"
#include "Component/animation_2d.h"

using namespace DG;

void Renderer::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::RENDERER;

		material_ = dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));
	}
	catch (std::exception const& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
}

void Renderer::set_mesh(std::string const& _tag)
{
	mesh_ = ResourceManager::singleton()->FindMesh(_tag);
}

void Renderer::set_mesh(std::shared_ptr<Mesh> const& _mesh)
{
	mesh_ = _mesh;
}

void Renderer::set_shader(std::string const& _tag)
{
	shader_ = RenderingManager::singleton()->FindShader(_tag);
}

void Renderer::set_shader(std::shared_ptr<Shader> const& _shader)
{
	shader_ = _shader;
}

void Renderer::set_render_state(std::string const& _tag)
{
	auto const& state = RenderingManager::singleton()->FindRenderState(_tag);

	if (!state)
		throw std::exception{ "Renderer::set_render_state" };

	render_state_array_.at(static_cast<int>(state->type())) = state;
}

Renderer::Renderer(Renderer const& _other) : Component(_other)
{
	mesh_ = _other.mesh_;
	shader_ = _other.shader_;
}

Renderer::Renderer(Renderer&& _other) noexcept : Component(std::move(_other))
{
	mesh_ = std::move(_other.mesh_);
	shader_ = std::move(_other.shader_);
}

void Renderer::_Release()
{
}

void Renderer::_Render(float _time)
{
	auto const& animation_2d = std::dynamic_pointer_cast<Animation2D>(object()->FindComponent(COMPONENT_TYPE::ANIMATION_2D));

	if(animation_2d)
		animation_2d->UpdateAnimation2DConstantBuffer(_time);

	_UpdateTransform();

	shader_->SetShader();

	for (auto const& _e : render_state_array_)
	{
		if(_e)
			_e->_SetState();
	}

	for (auto i = 0; i < mesh_->GetContainerSize(); ++i)
	{
		for (auto j = 0; j < mesh_->GetSubsetSize(i); ++j)
		{
			material_->SetToShader(i, j);

			mesh_->Render(i, j);
		}
	}

	for (auto const& _e : render_state_array_)
	{
		if (_e)
			_e->_SetBackState();
	}
}

std::unique_ptr<Component, std::function<void(Component*)>> Renderer::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Renderer{ *this }, [](Component* _p) {
		dynamic_cast<Renderer*>(_p)->_Release();
		delete dynamic_cast<Renderer*>(_p);
	} };
}

void Renderer::_UpdateTransform()
{
	auto const& camera = scene()->main_camera();
	auto const& camera_component = dynamic_pointer_cast<Camera>(camera->FindComponent(camera->tag()));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = transform->world();
	transform_constant_buffer.view = camera_component->view();
	transform_constant_buffer.projection = camera_component->projection();
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;
	transform_constant_buffer.pivot = transform->pivot();
	transform_constant_buffer.diagonal = mesh_->diagonal();

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);
}
