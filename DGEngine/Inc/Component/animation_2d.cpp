#include "DGEngine_stdafx.h"
#include "animation_2d.h"

#include "Resource/resource_manager.h"
#include "Rendering/rendering_manager.h"
#include "object.h"
#include "Component/material.h"

using namespace DG;

std::shared_ptr<Animation2DClipDesc> Animation2D::animation_2d_clip_nullptr_{};

void Animation2D::Initialize()
{
	type_ = COMPONENT_TYPE::ANIMATION_2D;
}

void Animation2D::AddClip(std::string const& _tag)
{
	auto const& animation_2d_clip = ResourceManager::singleton()->FindAnimation2DClip(_tag);

	if (!animation_2d_clip)
		throw std::exception{ "Animation2D::_AddClip" };

	if (default_clip_tag_.empty())
		default_clip_tag_ = _tag;

	if (!current_clip_)
		current_clip_ = animation_2d_clip;

	animation_2d_clip_map_.insert(make_pair(_tag, animation_2d_clip));
}

std::shared_ptr<Animation2DClipDesc> const& Animation2D::FindAnimation2DClip(std::string const& _tag) const
{
	auto iter = animation_2d_clip_map_.find(_tag);

	if (iter == animation_2d_clip_map_.end())
		return animation_2d_clip_nullptr_;
	
	return iter->second;
}

void Animation2D::SetDefaultClip(std::shared_ptr<Animation2DClipDesc> const& _animation_2d_clip)
{
	current_clip_ = _animation_2d_clip;
}

void Animation2D::ChangeClip(std::string const& _tag)
{
	if (current_clip_->animation_tag == _tag)
		return;

	auto const& clip = FindAnimation2DClip(_tag);

	if (!clip)
		return;

	current_clip_ = clip;

	frame_idx_ = 0;
	elapsed_time_ = 0.f;

	auto const& material = std::dynamic_pointer_cast<Material>(object()->FindComponent(COMPONENT_TYPE::MATERIAL));

	material->SetTexture(current_clip_->texture_tag, 0, 0, 0);
}

Animation2D::Animation2D(Animation2D const& _other) : Component(_other)
{
	frame_idx_ = _other.frame_idx_;
	elapsed_time_ = _other.elapsed_time_;
	animation_2d_clip_map_ = _other.animation_2d_clip_map_;
	current_clip_ = _other.current_clip_;
	default_clip_tag_ = _other.default_clip_tag_;
}

Animation2D::Animation2D(Animation2D&& _other) noexcept : Component(std::move(_other))
{
	frame_idx_ = std::move(_other.frame_idx_);
	elapsed_time_ = std::move(_other.elapsed_time_);
	animation_2d_clip_map_ = std::move(_other.animation_2d_clip_map_);
	current_clip_ = std::move(_other.current_clip_);
	default_clip_tag_ = std::move(_other.default_clip_tag_);
}

void Animation2D::_Release()
{
}

void Animation2D::_LateUpdate(float _time)
{
	elapsed_time_ += _time;

	float interval = current_clip_->completion_time / current_clip_->frame_vector.size();

	while (elapsed_time_ >= interval)
	{
		elapsed_time_ -= interval;

		++frame_idx_;

		if (frame_idx_ >= current_clip_->frame_vector.size())
		{
			frame_idx_ = 0;

			switch (current_clip_->option)
			{
			case ANIMATION_OPTION::DESTROY:
				object()->set_active_flag(false);
				break;
			}
		}
	}

	Animation2DConstantBuffer animation_2d_constant_buffer{};

	if (current_clip_->type == ANIMATION_2D_TYPE::ATLAS)
	{
		animation_2d_constant_buffer.UVLT.x = current_clip_->frame_vector.at(frame_idx_).LT.x / current_clip_->width;
		animation_2d_constant_buffer.UVLT.y = current_clip_->frame_vector.at(frame_idx_).LT.y / current_clip_->height;
		animation_2d_constant_buffer.UVRB.x = current_clip_->frame_vector.at(frame_idx_).RB.x / current_clip_->width;
		animation_2d_constant_buffer.UVRB.y = current_clip_->frame_vector.at(frame_idx_).RB.y / current_clip_->height;
	}
	else
	{
		animation_2d_constant_buffer.UVLT = Math::Vector2{ 0.f, 0.f };
		animation_2d_constant_buffer.UVRB = Math::Vector2{ 1.f, 1.f };
	}

	RenderingManager::singleton()->UpdateConstantBuffer("Animation2D", &animation_2d_constant_buffer);
}

std::unique_ptr<Component, std::function<void(Component*)>> Animation2D::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Animation2D{ *this }, [](Component* _p) {
		dynamic_cast<Animation2D*>(_p)->_Release();
		delete dynamic_cast<Animation2D*>(_p);
	} };
}
