#pragma once

using namespace DG;

template <typename T>
void InputMemoryStream::Read(T& _data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "InputMemoryStream::Read");

	// 인텔은 리틀엔디안, 네트워크는 빅엔디안 -> 스왑필요
	T swapped_data = ByteSwap(_data);
	Read(&swapped_data, sizeof(swapped_data));
}