#pragma once

using namespace DG;

template <typename T>
void InputMemoryStream::Read(T& _data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "InputMemoryStream::Read");

	// 만약 엔디언이 서로 같다면
	// Read(&_data, sizeof(_data));
	// return;

	// 인텔은 리틀엔디안, 네트워크는 빅엔디안 -> 스왑필요
	T swapped_data = ByteSwap(_data);
	Read(&swapped_data, sizeof(swapped_data));
}

template <typename T>
void InputMemoryStream::Read(std::vector<T>& _element_vector)
{
	size_t element_count{};

	Read(element_count);

	_element_vector.resize(element_count);

	for (auto& _element : _element_vector)
		Read(_element);
}