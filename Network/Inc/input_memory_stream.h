#pragma once

#include "singleton_temp.h"
#include "memory_stream.h"

namespace DG
{
	// LinkingContext 필요

	// Byte
	class DG_NETWORK_DLL InputMemoryStream : public MemoryStream, public Singleton_Temp<InputMemoryStream>
	{
		friend class Singleton_Temp<InputMemoryStream>;
	public:
		virtual void Initialize() override;

		virtual void Serialize(void* _data, uint32_t _byte_count) override;
		virtual bool IsInput() const override;

		void PreProcess();

		char const* GetBufferPtr() const;
		uint32_t GetLength() const;
		
		uint32_t GetRemainingDataSize() const;

		void Read(void* _data, uint32_t _byte_size);
		template <typename T> void Read(T& _data);
		template <typename T> void Read(std::vector<T>& _element_vector);

	private:
		InputMemoryStream() = default;
		InputMemoryStream(InputMemoryStream const&) = delete;
		InputMemoryStream(InputMemoryStream&&) noexcept = delete;
		InputMemoryStream& operator=(InputMemoryStream const&) = delete;
		InputMemoryStream& operator=(InputMemoryStream&&) noexcept = delete;

		virtual void _Release() override;

		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t head_{};
		uint32_t capacity_{};
	};

	// Bit
	class DG_NETWORK_DLL InputMemoryBitsStream : public Singleton_Temp<InputMemoryBitsStream>
	{
		friend class Singleton_Temp<InputMemoryBitsStream>;
	public:
		virtual void Initialize() override;
		void PreProcess();

		//template <typename T> void Write(T const& _data, size_t _bit_count = sizeof(T) * 8); // bool 타입 특수화 필요.
		void ReadBits(uint8_t& _data, size_t _bit_count);
		void ReadBits(void* _data, size_t _bit_count);
		void ReadBytes(void* _data, size_t _byte_count);

		char const* GetBufferPtr() const;
		uint32_t GetRemainingBitCount() const;

	private:
		InputMemoryBitsStream() = default;
		InputMemoryBitsStream(InputMemoryBitsStream const&) = delete;
		InputMemoryBitsStream(InputMemoryBitsStream&&) noexcept = delete;
		InputMemoryBitsStream& operator=(InputMemoryBitsStream const&) = delete;
		InputMemoryBitsStream& operator=(InputMemoryBitsStream&&) noexcept = delete;

		virtual void _Release() override;

		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t bit_head_{};
		uint32_t bit_capacity_{};
	};
}

#include "input_memory_stream.inl"