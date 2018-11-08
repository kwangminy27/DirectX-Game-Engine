#include "DGNetwork_stdafx.h"
#include "output_memory_stream.h"

using namespace DG;

void OutputMemoryStream::Initialize()
{
	buffer_ = static_cast<char*>(std::malloc(STREAM_BUFFER_DEFAULT_SIZE));
	head_ = 0;
	capacity_ = STREAM_BUFFER_DEFAULT_SIZE;
}

void OutputMemoryStream::PreProcess()
{
	head_ = 0;
}

char const* OutputMemoryStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t OutputMemoryStream::GetLength() const
{
	return head_;
}

void OutputMemoryStream::Write(void const* _data, size_t _byte_count)
{
	uint32_t result_head = head_ + static_cast<uint32_t>(_byte_count);

	if (result_head >= capacity_)
		_ReallocBuffer(std::max(capacity_ * 2, result_head));

	memcpy_s(buffer_ + head_, _byte_count, _data, _byte_count);

	head_ = result_head;
}

void OutputMemoryStream::_Release()
{
	std::free(buffer_);
}

void OutputMemoryStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::realloc(buffer_, _length));

	capacity_ = _length;
}

void OutputMemoryBitsStream::Initialize()
{
	buffer_ = static_cast<char*>(std::malloc(BIT_STREAM_BUFFER_DEFAULT_SIZE));
	bit_head_ = 0;
	bit_capacity_ = BIT_STREAM_BUFFER_DEFAULT_SIZE * 8;
}

void OutputMemoryBitsStream::PreProcess()
{
	bit_head_ = 0;
}

void OutputMemoryBitsStream::WriteBits(uint8_t _data, size_t _bit_count)
{
	// bit_head_�� ������ ��Ʈ���� ����� ��Ʈ ��ġ�� ��Ÿ��.
	uint32_t next_bit_head = bit_head_ + static_cast<uint32_t>(_bit_count);

	if (next_bit_head >= bit_capacity_)
		_ReallocBuffer(std::max(bit_capacity_ * 2, next_bit_head));

	// ���� buffer_�� ��ϵǾ� �ִ� ������ �������� ����Ʈ offset�� bit offset�� ���Ѵ�.
	uint32_t byte_offset = bit_head_ >> 3; // byte_offset�� ������ ��Ʈ�� ���Ե� ����Ʈ �ε����� ��Ÿ��.
	uint32_t bit_offset = bit_head_ & 0x7;

	uint8_t current_mask = ~(0xff << bit_offset);
	buffer_[byte_offset] = (buffer_[byte_offset] & current_mask) | (_data << bit_offset); // (_data << bit_offset): ����� �����͸� �������� ����Ʈ ��Ŵ

	// bit_head_: 0xff, ######11
	// byte_offset: 1
	// bit_offset: 2

	// 11111111, 2
	// 11111100
	// 00000011: current_mask

	// buffer_[byte_offset] & current_mask -> 00000011
	// _data << bit_offset -> ######00

	uint8_t free_bits_on_this_byte = 8 - bit_offset; // ���� ����Ʈ�� ���� ��Ʈ ��
	if (free_bits_on_this_byte < _bit_count)
		buffer_[byte_offset + 1] = _data >> free_bits_on_this_byte;

	bit_head_ = next_bit_head;
}

void OutputMemoryBitsStream::WriteBits(void const* _data, size_t _bit_count)
{
	char const* src_byte = static_cast<char const*>(_data);

	while (_bit_count > 8)
	{
		WriteBits(*src_byte, 8);
		++src_byte;
		_bit_count -= 8;
	}

	if (_bit_count > 0)
		WriteBits(*src_byte, _bit_count);
}

void OutputMemoryBitsStream::WriteBytes(void const* _data, size_t _byte_count)
{
	WriteBits(_data, _byte_count << 3);
}

char const* OutputMemoryBitsStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t OutputMemoryBitsStream::GetBitLength() const
{
	return bit_head_;
}

uint32_t OutputMemoryBitsStream::GetByteLength() const
{
	return (bit_head_ + 7) >> 3; // �ּ� �� ����Ʈ�� ǥ���� �� �ִ����� ��Ÿ��
	// 0 -> 0
	// 1 -> 1
	// 2 -> 1
	// ...
	// 8 -> 1
	// 9 -> 2
}

void OutputMemoryBitsStream::_Release()
{
	std::free(buffer_);
}

void OutputMemoryBitsStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::realloc(buffer_, _length));

	bit_capacity_ = _length * 8;
}
