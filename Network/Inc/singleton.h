#pragma once

namespace DG
{
	template <typename T>
	class Singleton
	{
	public:
		static std::unique_ptr<T, std::function<void(T*)>>& singleton();

	protected:
		Singleton() = default;
		Singleton(Singleton const&) = delete;
		Singleton(Singleton&&) noexcept = delete;
		Singleton& operator=(Singleton const&) = delete;
		Singleton& operator=(Singleton&&) noexcept = delete;

		virtual void _Release() = 0;

		static std::unique_ptr<T, std::function<void(T*)>> singleton_;
		static std::once_flag once_flag_;
	};
}

#include "singleton.inl"