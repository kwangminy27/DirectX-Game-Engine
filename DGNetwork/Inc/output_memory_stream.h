#pragma once

namespace DG
{
	class OutputMemoryStream
	{
	public:
		OutputMemoryStream() = default;
		~OutputMemoryStream();

		char const* GetBufferPtr() const;
		uint32_t GetLength() const;

		template <typename T> void Write(T const& _data);
		void Write(void const* _data, size_t _byte_count);

	private:
		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t head_{};
		uint32_t capacity_{};
	};
}

#include "output_memory_stream.inl"
