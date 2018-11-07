#include "DGNetwork_stdafx.h"
#include "input_memory_stream.h"

using namespace DG;

// Byte
void InputMemoryStream::Initialize()
{
	buffer_ = static_cast<char*>(std::malloc(STREAM_BUFFER_DEFAULT_SIZE));
	head_ = 0;
	capacity_ = 1024;
}

void InputMemoryStream::PreProcess()
{
	head_ = 0;
}

char const* InputMemoryStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t InputMemoryStream::GetLength() const
{
	return head_;
}

uint32_t InputMemoryStream::GetRemainingDataSize() const
{
	return capacity_ - head_;
}

void InputMemoryStream::Read(void* _data, uint32_t _byte_size)
{
	uint32_t result_byte_size = std::max(GetRemainingDataSize(), _byte_size);

	if (result_byte_size + head_ >= capacity_)
		_ReallocBuffer(std::max(capacity_ * 2, result_byte_size + head_));

	memcpy_s(_data, result_byte_size, buffer_ + head_, result_byte_size);

	head_ += result_byte_size;
}

void InputMemoryStream::_Release()
{
	std::free(buffer_);
}

void InputMemoryStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::realloc(buffer_, _length));

	capacity_ = _length;
}

// Bit
void InputMemoryBitsStream::Initialize()
{
	buffer_ = static_cast<char*>(std::malloc(BIT_STREAM_BUFFER_DEFAULT_SIZE));
	bit_head_ = 0;
	bit_capacity_ = BIT_STREAM_BUFFER_DEFAULT_SIZE * 8;
}

void InputMemoryBitsStream::PreProcess()
{
	bit_head_ = 0;
}

void InputMemoryBitsStream::ReadBits(uint8_t& _data, size_t _bit_count)
{
	uint32_t byte_offset = bit_head_ >> 3;
	uint32_t bit_offset = bit_head_ & 0x7;

	_data = static_cast<uint8_t>(buffer_[byte_offset]) >> bit_offset;

	uint8_t bits_free_on_this_byte = 8 - bit_offset;

	if (bits_free_on_this_byte < _bit_count)
		_data |= static_cast<uint8_t>(buffer_[byte_offset + 1]) << bits_free_on_this_byte;

	_data &= ~(0xff << _bit_count);

	bit_head_ += static_cast<uint32_t>(_bit_count);
}

void InputMemoryBitsStream::ReadBits(void* _data, size_t _bit_count)
{
	uint8_t* dest_byte = static_cast<uint8_t*>(_data);

	while (_bit_count > 8)
	{
		ReadBits(*dest_byte, 8);
		++dest_byte;
		_bit_count -= 8;
	}

	if (_bit_count > 0)
		ReadBits(*dest_byte, _bit_count);
}

void InputMemoryBitsStream::ReadBytes(void* _data, size_t _byte_count)
{
	ReadBits(_data, _byte_count << 3);
}

char const* InputMemoryBitsStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t InputMemoryBitsStream::GetRemainingBitCount() const
{
	return bit_capacity_ - bit_head_;
}

void InputMemoryBitsStream::_Release()
{
	std::free(buffer_);
}

void InputMemoryBitsStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::malloc(_length));

	bit_capacity_ = _length * 8;
}
