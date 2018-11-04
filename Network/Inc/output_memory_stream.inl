#pragma once

using namespace DG;

template <typename T>
void OutputMemoryStream::Write(T const& _data)
{
	// arithmetic이나 enum인 경우만 처리
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryStream::Write");
	
	// 인텔은 리틀엔디안, 네트워크는 빅엔디안 -> 스왑필요
	T swapped_data = ByteSwap(_data);
	Write(&swapped_data, sizeof(swapped_data));
}