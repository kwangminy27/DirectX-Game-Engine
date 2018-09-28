#include "DGEngine_stdafx.h"
#include "tag.h"

std::string const& DG::Tag::tag() const
{
	return tag_;
}

bool DG::Tag::active_flag() const
{
	return active_flag_;
}

bool DG::Tag::enable_flag() const
{
	return enable_flag_;
}

void DG::Tag::set_tag(std::string const& _tag)
{
	tag_ = _tag;
}

void DG::Tag::set_active_flag(bool _flag)
{
	active_flag_ = _flag;
}

void DG::Tag::set_enable_flag(bool _flag)
{
	enable_flag_ = _flag;
}

DG::Tag::Tag(DG::Tag const& _other)
{
	*this = _other;
}

DG::Tag::Tag(DG::Tag&& _other) noexcept
{
	*this = std::move(_other);
}
