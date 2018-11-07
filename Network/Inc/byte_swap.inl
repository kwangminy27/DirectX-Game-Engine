#pragma once

using namespace DG;

template <typename from, typename to>
TypeAliaser<from, to>::TypeAliaser(from _data)
{
	from_type_ = _data;
}

template <typename from, typename to>
to& TypeAliaser<from, to>::Get()
{
	return to_type_;
}

template <typename T>
T ByteSwapper<T, 2>::Swap(T _data) const
{
	uint16_t result = ByteSwap2(TypeAliaser<T, uint16_t>(_data).Get());
	return TypeAliaser<uint16_t, T>(result).Get();
}

template <typename T>
T ByteSwapper<T, 4>::Swap(T _data) const
{
	uint32_t result = ByteSwap4(TypeAliaser<T, uint32_t>(_data).Get());
	return TypeAliaser<uint32_t, T>(result).Get();
}

template <typename T>
T ByteSwapper<T, 8>::Swap(T _data) const
{
	uint64_t result = ByteSwap8(TypeAliaser<T, uint64_t>(_data).Get());
	return TypeAliaser<uint64_t, T>(result).Get();
}

template <typename T>
T ByteSwap(T _data)
{
	return ByteSwapper<T, sizeof(T)>{}.Swap(_data);
}
