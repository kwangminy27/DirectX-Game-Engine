#include "DGEngine_stdafx.h"
#include "slot_UI.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "input_manager.h"

using namespace DG;

void SlotUI::Initialize()
{
	try
	{
		UI::Initialize();

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

		transform->Scaling({ 36.f, 36.f, 1.f });
		transform->Translation({ 300.f, 100.f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BASIC_TEX_SHADER);
		renderer->set_mesh_tag("TexRect");
		renderer->set_render_state(ALPHA_BLEND);

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("Slot", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("SlotBody"));
		auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
		auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

		collider_rect->set_collision_group_tag("UI");
		collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
		collider_rect->AddSkipTag("IconBody");
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "SlotUI::Initialize()" << std::endl;
	}
}

SlotUI::SlotUI(SlotUI const& _other) : UI(_other)
{
}

SlotUI::SlotUI(SlotUI&& _other) noexcept : UI(std::move(_other))
{
}

void SlotUI::_Release()
{
}

void SlotUI::_Input(float _time)
{
	auto const& input_manager = InputManager::singleton();
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (input_manager->KeyPressed("U"))
		transform->RotationZ(DirectX::XMConvertToRadians(180.f * _time));
	if (input_manager->KeyPressed("I"))
		transform->RotationZ(DirectX::XMConvertToRadians(-180.f * _time));
	if (input_manager->KeyPressed("O"))
		transform->Translation(transform->GetWorldUp() * 400.f * _time);
	if (input_manager->KeyPressed("P"))
		transform->Translation(transform->GetWorldUp() * -400.f * _time);
}

void SlotUI::_Update(float _time)
{
}

void SlotUI::_LateUpdate(float _time)
{
}

void SlotUI::_Collision(float _time)
{
}

void SlotUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> SlotUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new SlotUI{ *this }, [](Component* _p) {
		dynamic_cast<SlotUI*>(_p)->_Release();
		delete dynamic_cast<SlotUI*>(_p);
	} };
}

void SlotUI::_AfterClone()
{
}
