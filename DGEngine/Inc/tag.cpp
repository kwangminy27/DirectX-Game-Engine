#include "DGEngine_stdafx.h"
#include "tag.h"

using namespace DG;

std::string const& Tag::tag() const
{
	return tag_;
}

bool Tag::active_flag() const
{
	return active_flag_;
}

bool Tag::enable_flag() const
{
	return enable_flag_;
}

void Tag::set_tag(std::string const& _tag)
{
	tag_ = _tag;
}

void Tag::set_active_flag(bool _flag)
{
	active_flag_ = _flag;
}

void Tag::set_enable_flag(bool _flag)
{
	enable_flag_ = _flag;
}

Tag::Tag(Tag const& _other)
{
	*this = _other;
}

Tag::Tag(Tag&& _other) noexcept
{
	*this = std::move(_other);
}
