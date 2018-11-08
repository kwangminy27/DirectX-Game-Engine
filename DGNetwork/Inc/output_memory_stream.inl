#pragma once

using namespace DG;

template <typename T>
void OutputMemoryStream::Write(T const& _data)
{
	// arithmetic�̳� enum�� ��츸 ó��
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryStream::Write");
	
	// ���� ������� ���� ���ٸ�
	// Write(&_data, sizeof(_data));
	// return;

	// ������ ��Ʋ �����, ��Ʈ��ũ�� �� ����� -> �����ʿ�
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
	// �ּ� �Ҵ� ��� ������, ��Ʋ ����𿡼��� ����
	// �� ����𿡼��� �����ϰ� �� �ϰ� �ʹٸ� ByteSwap �ʿ�

	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryBitsStream::Write");

	// ���� ������� ���� �ٸ��ٸ�
	// T swapped_data = ByteSwap(_data);
	// WriteBits(&swap_data, sizeof(swap_data));

	WriteBits(&_data, _bit_count);
}
