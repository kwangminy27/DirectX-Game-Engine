#pragma once

#include "singleton_temp.h"

namespace DG
{
	class DG_NETWORK_DLL InputMemoryStream : public Singleton_Temp<InputMemoryStream>
	{
		friend class Singleton_Temp<InputMemoryStream>;
	public:
		virtual void Initialize() override;
		void PreProcess();

		char const* GetBufferPtr() const;
		uint32_t GetLength() const;
		
		uint32_t GetRemainingDataSize() const;

		template <typename T> void Read(T& _data);
		void Read(void* _data, uint32_t _byte_size);

	private:
		InputMemoryStream() = default;
		InputMemoryStream(InputMemoryStream const&) = delete;
		InputMemoryStream(InputMemoryStream&&) noexcept = delete;
		InputMemoryStream& operator=(InputMemoryStream const&) = delete;
		InputMemoryStream& operator=(InputMemoryStream&&) noexcept = delete;

		virtual void _Release() override;

		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t head_{};
		uint32_t capacity_{};
	};
}

#include "input_memory_stream.inl"