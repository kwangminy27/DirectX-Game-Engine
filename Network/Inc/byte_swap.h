#pragma once

namespace DG
{
	// ByteSwap 함수, 부호 없는 정수만 뒤집을 수 있음
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

	// float, double, 부호 있는 정수, 열거자 등을 지원하기 위한 별칭 클래스
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

	// "리틀 엔디언 <-> 빅 엔디언"을 위한 보조 클래스
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

	// "리틀 엔디언 <-> 빅 엔디언"을 위한 클래스를 호출해주는 보조 함수, 원시 자료형에 한하여 바이트 스와핑 해야한다고 함.
	template <typename T>
	T ByteSwap(T _data);
}

#include "byte_swap.inl"