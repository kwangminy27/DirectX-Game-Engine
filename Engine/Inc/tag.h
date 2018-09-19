#pragma once

namespace DG
{
	class Tag
	{
	public:
		std::string const& tag() const;
		bool activation() const;
		bool enablement() const;

		void set_tag(std::string const& _tag);
		void set_activation(bool _boolean);
		void set_enablement(bool _boolean);

	protected:
		Tag() = default;
		Tag(Tag const&) = delete;
		Tag(Tag&&) noexcept = delete;
		Tag& operator=(Tag const&) = delete;
		Tag& operator=(Tag&&) noexcept = delete;

		virtual void _Release() = 0;

		std::string tag_{};
		bool activation_{ true };
		bool enablement_{ true };
	};
}