#pragma once

namespace DG
{
	template <typename T>
	class Singleton_Temp
	{
	public:
		static std::unique_ptr<T, std::function<void(T*)>>& singleton();

	protected:
		Singleton_Temp() = default;
		Singleton_Temp(Singleton_Temp const&) = delete;
		Singleton_Temp(Singleton_Temp&&) noexcept = delete;
		Singleton_Temp& operator=(Singleton_Temp const&) = delete;
		Singleton_Temp& operator=(Singleton_Temp&&) noexcept = delete;

		virtual void _Release() = 0;

		static std::unique_ptr<T, std::function<void(T*)>> singleton_;
		static std::once_flag once_flag_;
	};
}

#include "singleton_temp.inl"