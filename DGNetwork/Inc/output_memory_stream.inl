#pragma once

using namespace DG;

template <typename T>
void OutputMemoryStream::Write(T const& _data)
{
	// arithmetic이나 enum인 경우만 처리
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryStream::Write");
	
	// 만약 엔디언이 서로 같다면
	// Write(&_data, sizeof(_data));
	// return;

	// 인텔은 리틀 엔디안, 네트워크는 빅 엔디안 -> 스왑필요
	T swapped_data = ByteSwap(_data);
	Write(&swapped_data, sizeof(swapped_data));
}

template <typename T>
void OutputMemoryStream::Write(std::vector<T> const& _element_vector)
{
	size_t element_count = _element_vector.size();

	Write(element_count);

	for (auto const& _element : _element_vector)
		Write(_element);
}

template<typename T>
void OutputMemoryBitsStream::Write(T const& _data, size_t _bit_count)
{
	// 주소 할당 방식 때문에, 리틀 엔디언에서만 동작
	// 빅 엔디언에서도 동작하게 끔 하고 싶다면 ByteSwap 필요

	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryBitsStream::Write");

	// 만약 엔디언이 서로 다르다면
	// T swapped_data = ByteSwap(_data);
	// WriteBits(&swap_data, sizeof(swap_data));

	WriteBits(&_data, _bit_count);
}
