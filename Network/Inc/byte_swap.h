#pragma once

namespace DG
{
	inline uint16_t ByteSwap2(uint16_t _data)
	{
		return _data >> 8 | _data << 8;
	}

	inline uint32_t ByteSwap4(uint32_t _data)
	{
		return ((_data >> 24) & 0x000000FF) |
			((_data >> 8) & 0x0000FF00) |
			((_data << 8) & 0x00FF0000) |
			((_data << 24) & 0xFF000000);
	}

	inline uint64_t ByteSwap8(uint64_t _data)
	{
		return ((_data >> 56) & 0x00000000000000FF) |
			((_data >> 40) & 0x000000000000FF00) |
			((_data >> 24) & 0x0000000000FF0000) |
			((_data >> 8) & 0x00000000FF000000) |
			((_data << 8) & 0x000000FF00000000) |
			((_data << 24) & 0x0000FF0000000000) |
			((_data << 40) & 0x00FF000000000000) |
			((_data << 56) & 0xFF00000000000000);
	}

	template <typename from, typename to>
	class TypeAliaser
	{
	public:
		TypeAliaser(from _data);

		to& Get();

		union
		{
			from from_type_;
			to to_type_;
		};
	};

	template <typename T, size_t size> class ByteSwapper;

	template <typename T>
	class ByteSwapper<T, 2>
	{
	public:
		T Swap(T _data) const;
	};

	template <typename T>
	class ByteSwapper<T, 4>
	{
	public:
		T Swap(T _data) const;
	};

	template <typename T>
	class ByteSwapper<T, 8>
	{
	public:
		T Swap(T _data) const;
	};

	template <typename T>
	T ByteSwap(T _data);
}

#include "byte_swap.inl"