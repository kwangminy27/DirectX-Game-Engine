#pragma once

namespace DG
{
	class MemoryStream
	{
	protected:
		template <typename T> void Serialize(T& _data);
		virtual void Serialize(void* _data, uint32_t _byte_count) = 0;
		virtual bool IsInput() const = 0;
	};

	constexpr int GetRequiredBits(int _value, int bits = 0)
	{
		return _value ? GetRequiredBits(_value >> 1, bits + 1) : bits;
	}
#include "memory_stream.inl"
}