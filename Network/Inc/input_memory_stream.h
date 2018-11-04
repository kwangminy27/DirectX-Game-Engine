#pragma once

namespace DG
{
	class InputMemoryStream
	{
	public:
		InputMemoryStream() = default;
		~InputMemoryStream();

		uint32_t GetRemainingDataSize() const;

		template <typename T> void Read(T& _data);
		void Read(void* _data, uint32_t _byte_size);

	private:
		char* buffer_{};
		uint32_t head_{};
		uint32_t capacity_{};
	};
}

#include "input_memory_stream.inl"