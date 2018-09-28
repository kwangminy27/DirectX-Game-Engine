#pragma once

namespace DG
{
	class DG_ENGINE_DLL Tag
	{
	public:
		std::string const& tag() const;
		bool active_flag() const;
		bool enable_flag() const;

		void set_tag(std::string const& _tag);
		void set_active_flag(bool _flag);
		void set_enable_flag(bool _flag);

	protected:
		Tag() = default;
		Tag(Tag const& _other);
		Tag(Tag&& _other) noexcept;
		Tag& operator=(Tag const&) = default;
		Tag& operator=(Tag&&) noexcept = default;

		virtual void _Release() = 0;

		std::string tag_{};
		bool active_flag_{ true };
		bool enable_flag_{ true };
	};
}