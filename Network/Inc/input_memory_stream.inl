#pragma once

using namespace DG;

template <typename T>
void InputMemoryStream::Read(T& _data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "InputMemoryStream::Read");

	// ���� ������� ���� ���ٸ�
	// Read(&_data, sizeof(_data));
	// return;

	// ������ ��Ʋ�����, ��Ʈ��ũ�� �򿣵�� -> �����ʿ�
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