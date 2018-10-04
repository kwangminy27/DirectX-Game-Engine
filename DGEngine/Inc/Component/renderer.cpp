#include "DGEngine_stdafx.h"
#include "renderer.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/material.h"

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
	_UpdateTransform();

	shader_->SetShader();

	for (auto i = 0; i < mesh_->GetContainerSize(); ++i)
	{
		for (auto j = 0; j < mesh_->GetSubsetSize(i); ++j)
		{
			material_->SetToShader(i, j);

			mesh_->Render(i, j);
		}
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

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM))->world();
	transform_constant_buffer.view = camera_component->view();
	transform_constant_buffer.projection = camera_component->projection();
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);
}
