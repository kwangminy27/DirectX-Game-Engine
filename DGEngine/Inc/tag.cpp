#include "DGEngine_stdafx.h"
#include "tag.h"

using namespace std;
using namespace DG;

string const& Tag::tag() const
{
	return tag_;
}

bool Tag::activation() const
{
	return activation_;
}

bool Tag::enablement() const
{
	return enablement_;
}

void Tag::set_tag(string const& _tag)
{
	tag_ = _tag;
}

void Tag::set_activation(bool _boolean)
{
	activation_ = _boolean;
}

void Tag::set_enablement(bool _boolean)
{
	enablement_ = _boolean;
}
