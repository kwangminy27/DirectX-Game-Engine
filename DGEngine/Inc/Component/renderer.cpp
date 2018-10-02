#include "DGEngine_stdafx.h"
#include "renderer.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "object.h"
#include "Component/transform.h"

using namespace DG;

void Renderer::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::RENDERER;
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
	mesh_->Render();
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
	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM))->world();
	transform_constant_buffer.view = DirectX::XMMatrixLookAtLH(Math::Vector3(0.f, 0.f, -5.f), Math::Vector3(0.f, 0.f, 0.f), Math::Vector3::UnitY);
	transform_constant_buffer.projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XM_PIDIV4,
		static_cast<float>(RESOLUTION::WIDTH) / static_cast<float>(RESOLUTION::HEIGHT),
		0.001f,
		1000.f
	);
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);
}
