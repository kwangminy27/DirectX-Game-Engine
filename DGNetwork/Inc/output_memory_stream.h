#pragma once

#include "singleton_temp.h"

namespace DG
{
	// LinkingContext 필요

	// Byte
	class DG_NETWORK_DLL OutputMemoryStream : public Singleton_Temp<OutputMemoryStream>
	{
		friend class Singleton_Temp<OutputMemoryStream>;
	public:
		virtual void Initialize() override;
		void PreProcess();

		char const* GetBufferPtr() const;
		uint32_t GetLength() const;

		void Write(void const* _data, size_t _byte_count);
		template <typename T> void Write(T const& _data);
		template <typename T> void Write(std::vector<T> const& _element_vector);

	private:
		OutputMemoryStream() = default;
		OutputMemoryStream(OutputMemoryStream const&) = delete;
		OutputMemoryStream(OutputMemoryStream&&) noexcept = delete;
		OutputMemoryStream& operator=(OutputMemoryStream const&) = delete;
		OutputMemoryStream& operator=(OutputMemoryStream&&) noexcept = delete;

		virtual void _Release() override;

		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t head_{};
		uint32_t capacity_{};
	};

	// Bit
	class DG_NETWORK_DLL OutputMemoryBitsStream : public Singleton_Temp<OutputMemoryStream>
	{
		friend class Singleton_Temp<OutputMemoryStream>;
	public:
		virtual void Initialize() override;
		void PreProcess();

		template <typename T> void Write(T const& _data, size_t _bit_count = sizeof(T) * 8); // bool 타입 특수화 필요.
		void WriteBits(uint8_t _data, size_t _bit_count);
		void WriteBits(void const* _data, size_t _bit_count);
		void WriteBytes(void const* _data, size_t _byte_count);

		char const* GetBufferPtr() const;
		uint32_t GetBitLength() const;
		uint32_t GetByteLength() const;

	private:
		OutputMemoryBitsStream() = default;
		OutputMemoryBitsStream(OutputMemoryBitsStream const&) = delete;
		OutputMemoryBitsStream(OutputMemoryBitsStream&&) noexcept = delete;
		OutputMemoryBitsStream& operator=(OutputMemoryBitsStream const&) = delete;
		OutputMemoryBitsStream& operator=(OutputMemoryBitsStream&&) noexcept = delete;

		virtual void _Release() override;

		void _ReallocBuffer(uint32_t _length);

		char* buffer_{};
		uint32_t bit_head_{};
		uint32_t bit_capacity_{};
	};
}

#include "output_memory_stream.inl"
