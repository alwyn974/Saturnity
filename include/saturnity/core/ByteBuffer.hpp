/*
** EPITECH PROJECT, 2023
** ByteBuffer.hpp
** File description:
** ByteBuffer.hpp
*/

#ifndef SATURNITY_BYTEBUFFER_HPP
#define SATURNITY_BYTEBUFFER_HPP

#include "Core.hpp"

#include <memory>
#include <vector>
#include <exception>
#include <stdexcept>

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A byte buffer class, limited to UINT32_MAX bytes
     */
    class ByteBuffer {
    public:
        SA_EXCEPTION(ReadOnlyException)

        /**
         * @brief Construct a byte buffer with a size
         * @param bufferSize the size of the buffer
         * @param readOnly specify if the byte buffer is only readeable (default: false)
         */
        explicit ByteBuffer(std::uint32_t bufferSize = SA_BUFFER_SIZE, bool readOnly = false);

        /**
         * @brief Construct a byte buffer from a vector of bytes
         * @param buffer the vector containing the bytes
         * @param readOnly specify if the byte buffer is only readeable (default: false)
         */
        explicit ByteBuffer(const std::vector<byte_t> &buffer, bool readOnly = false);

        /**
         * @brief Construct a byte buffer from a C style array
         * @param bytes the array of bytes
         * @param size the size of the array
         * @param readOnly specify if the byte buffer is only readeable (default: false)
         */
        explicit ByteBuffer(const byte_t *bytes, std::uint32_t size, bool readOnly = false);

        /**
         * @brief Clear the buffer and reset the read/write position
         */
        void clear();

        /**
         * @brief Check if the buffer is empty
         * @return true if the buffer is empty, false otherwise
         */
        bool isEmpty();

        /**
         * @brief Clone the bytebuffer with all the same state and data
         * @return a cloned ByteBuffer as unique_ptr
         */
        std::unique_ptr<ByteBuffer> clone();

        /**
         * @brief Retrive the size of the internal vector
         * @return the size of the vector
         */
        std::uint32_t size() const;

        /**
         * @brief Resize the ByteBuffer
         * @param size the new size of the ByteBuffer
         */
        void resize(std::uint32_t size);

        /**
         * @brief Check if the ByteBuffer is only readeable
         * @return true if the ByteBuffer is only readeable, false otherwise
         */
        bool isReadOnly() const;

        /**
         * @brief Get t nheber uomf bytes remaining in the buffer
         * @return the number of bytes remaining
         */
        std::uint32_t remainingBytes() const;

        /**
         * @brief Check if the buffer has enough space to write a certain size
         * @param size the size to check
         * @return true if the buffer has enough space, false otherwise
         */
        bool hasSpace(std::uint32_t size) const;

        //
        // Read methods
        //

        /**
         * @brief Read a byte from the buffer (increase the read position by 1)
         * @return the byte read
         */
        byte_t readByte();

        /**
         * @brief Read a boolean from the buffer (increase the read position by the size)
         * @param size the size of the bytes to read
         * @return the bytes read
         */
        std::vector<byte_t> readBytes(std::uint32_t size);

        /**
         * @brief Read bytes from the buffer (increase the read position by the size) from an offset
         * @param size the size of the bytes to read
         * @param offset the offset to read from
         * @return the bytes read
         */
        std::vector<byte_t> readBytes(std::uint32_t size, std::uint32_t offset);

        /**
         * @brief Read a boolean from the buffer (increase the read position by 1)
         * @return the boolean read
         */
        bool readBoolean();

        /**
         * @brief Read a short from the buffer (increase the read position by 2)
         * @return the short read
         */
        std::int16_t readShort();

        /**
         * @brief Read an unsigned short from the buffer (increase the read position by 2)
         * @return the unsigned short read
         */
        std::uint16_t readUShort();

        /**
         * @brief Read an int from the buffer (increase the read position by 4)
         * @return the int read
         */
        std::int32_t readInt();

        /**
         * @brief Read an unsigned int from the buffer (increase the read position by 4)
         * @return the unsigned int read
         */
        std::uint32_t readUInt();

        /**
         * @brief Read a long from the buffer (increase the read position by 8)
         * @return the long read
         */
        std::int64_t readLong();

        /**
         * @brief Read an unsigned long from the buffer (increase the read position by 8)
         * @return the unsigned long read
         */
        std::uint64_t readULong();

        /**
         * @brief Read a float from the buffer (increase the read position by 4)
         * @return the float read
         */
        float readFloat();

        /**
         * @brief Read a double from the buffer (increase the read position by 8)
         * @return the double read
         */
        double readDouble();

        /**
         * @brief Read a string from the buffer (increase the read position by 2 + the size of the string)
         * @return the string read
         */
        std::string readString();

        /**
         * @brief Read a variable length int from the buffer (increase the read position by 1 to 5)
         * @return the variable length int read
         * @throws std::runtime_error if the varint is too big
         */
        std::int32_t readVarInt();

        /**
         * @brief Read a variable length unsigned int from the buffer (increase the read position by 1 to 5)
         * @return the variable length unsigned int read
         * @throws std::runtime_error if the varuint is too big
         */
        std::uint32_t readVarUInt();

        /**
         * @brief Read a variable length long from the buffer (increase the read position by 1 to 10)
         * @return the variable length long read
         * @throws std::runtime_error if the varlong is too big
         */
        std::int64_t readVarLong();

        /**
         * @brief Read a variable length unsigned long from the buffer (increase the read position by 1 to 10)
         * @return the variable length unsigned long read
         * @throws std::runtime_error if the varulong is too big
         */
        std::uint64_t readVarULong();

        //
        // Write methods
        //

        /**
         * @brief Write a byte in the buffer, (increase the write position by 1)
         * @param byte the byte to write
         * @throws ReadOnlyException if the ByteBuffer is only readeable
         */
        void writeByte(const byte_t &byte);

        /**
         * @brief Write a vector of bytes in the buffer (increase the write position by the size of the vector)
         * @param buffer the byte buffer to write
         */
        void writeBytes(const ByteBuffer &buffer);

        /**
         * @brief Write a vector of bytes in the buffer (increase the write position by the size of the vector)
         * @param bytes the vector of bytes to write
         */
        void writeBytes(const std::vector<byte_t> &bytes);

        /**
         * @brief Write a vector of bytes in the buffer (increase the write position by the size of the vector)
         * @param bytes the vector of bytes to write
         * @param size the size of the vector
         */
        void writeBytes(const byte_t *bytes, std::uint32_t size);

        /**
         * @brief Write a boolean in the buffer (increase the write position by 1)
         * @param value the value to write
         */
        void writeBoolean(bool value);

        /**
         * @brief Write a short in the buffer (increase the write position by 2)
         * @param value the value to write
         */
        void writeShort(std::int16_t value);

        /**
         * @brief Write a unsigned short in the buffer (increase the write position by 2)
         * @param value the value to write
         */
        void writeUShort(std::uint16_t value);

        /**
         * @brief Write a int in the buffer (increase the write position by 4)
         * @param value the value to write
         */
        void writeInt(std::int32_t value);

        /**
         * @brief Write a unsigned int in the buffer (increase the write position by 4)
         * @param value the value to write
         */
        void writeUInt(std::uint32_t value);

        /**
         * @brief Write a long in the buffer (increase the write position by 8)
         * @param value the value to write
         */
        void writeLong(std::int64_t value);

        /**
         * @brief Write a unsigned long in the buffer (increase the write position by 8)
         * @param value the value to write
         */
        void writeULong(std::uint64_t value);

        /**
         * @brief Write a float in the buffer (increase the write position by 4)
         * @param value the value to write
         */
        void writeFloat(float value);

        /**
         * @brief Write a double in the buffer (increase the write position by 8)
         * @param value the value to write
         */
        void writeDouble(double value);

        /**
         * @brief Write a string in the buffer (increase the write position by the 2 + size of the string)
         * @param str the string to write
         */
        void writeString(const std::string &str);

        /**
         * @brief Write a var int in the buffer (minimum 1 byte, maximum 5 bytes)
         * @param value the value to write
         */
        void writeVarInt(std::int32_t value);

        /**
         * @brief Write a var uint in the buffer (minimum 1 byte, maximum 5 bytes)
         * @param value the value to write
         */
        void writeVarUInt(std::uint32_t value);

        /**
         * @brief Write a var long in the buffer (minimum 1 byte, maximum 10 bytes)
         * @param value the value to write
         */
        void writeVarLong(std::int64_t value);

        /**
         * @brief Write a var ulong in the buffer (minimum 1 byte, maximum 10 bytes)
         * @param value the value to write
         */
        void writeVarULong(std::uint64_t value);

        //
        // Utils methods
        //

        /**
         * @brief Return the vector used as buffer to store bytes
         * @return the vector
         */
        std::vector<byte_t> &vector();

        /**
         * @brief Return the vector used as buffer to store bytes
         * @return the vector
         */
        const std::vector<byte_t> &getBuffer() const;

        /**
         * @brief Compare two byte buffer for equality (size and bytes are compared)
         * @param other the ByteBuffer to compare with
         * @return true if the ByteBuffer are the same, false otherwise
         */
        bool operator==(const ByteBuffer &other) const;

        /**
         * @brief  Compare two byte buffer for inequality (size and bytes are compared)
         * @param other the ByteBuffer to compare with
         * @return true if the ByteBuffer are not the same, false otherwise
         */
        bool operator!=(const ByteBuffer &other) const;

        /**
         * @brief Get the current index of the reader
         * @return the current index of the reader
         */
        std::uint32_t readerIndex() const;

        /**
         * @brief Set the current reader index
         * @param readerIndex the new index of the reader
         * @throws std::out_of_range if the index is out of bounds (limit is @link ByteBuffer::_maxCapacity)
         */
        void setReaderIndex(std::uint32_t readerIndex);

        /**
         * @brief Reset the reader index to 0
         */
        void resetReaderIndex();

        /**
         * @brief Get the current writer index
         * @return the current index of the writer
         */
        std::uint32_t writerIndex() const;

        /**
         * @brief Set the current writer index
         * @param writerIndex the new index of the writer
         * @throws std::out_of_range if the index is out of bounds (limit is @link ByteBuffer::_maxCapacity)
         */
        void setWriterIndex(std::uint32_t writerIndex);

        /**
         * @brief Reset the writer index to 0
         */
        void resetWriterIndex();

        /**
         * @brief Get the size of a var int
         * @param value the value of the var int
         * @return the size of the var int
         */
        static int getVarIntSize(std::int32_t value);

        /**
         * @brief Get the size of a var unsigned int
         * @param value the value of the var unsigined int
         * @return the size of the var unsigned int
         */
        static int getVarUIntSize(std::uint32_t value);

        /**
         * @brief Get the size of a var long
         * @param value the value of the var long
         * @return the size of the var long
         */
        static int getVarLongSize(std::int64_t value);

        /**
         * @brief Get the size of a var unsigned long
         * @param value the value of the var unsigned long
         * @return the size of the var unsigned long
         */
        static int getVarULongSize(std::uint64_t value);

        static inline const constexpr int MAX_VARINT_SIZE = 5; /**< The maximum size of the var (u)int */
        static inline const constexpr int MAX_VARLONG_SIZE = 10; /**< The maximum size of the var (u)long */
        static inline const constexpr std::uint32_t SEGMENT_BITS = 0x7F; /**< The segment bits is used to extract the least significant bit (7-bit chunk) */
        static inline const constexpr std::uint32_t CONTINUE_BIT = 0x80; /**< The continuation bit is used as a flag, to check if more bytes need to be read */

    protected:
        /**
         * @brief Read a value from the buffer, change the reader index
         * @tparam T the type of the value to read
         * @return the value read
         */
        template<typename T>
        T read();

        /**
         * @brief Read a value from the buffer at a certain offset, change the reader index
         * @tparam T the type of the value to read
         * @param offset the offset to read the value
         * @return the value read
         * @throws std::out_of_range if the offset is out of bounds (limit is @link ByteBuffer::_maxCapacity)
         */
        template<typename T>
        T read(std::uint32_t offset);

        /**
         * @brief Write a value in the buffer, change the writer index (capacity is increased if needed)
         * @tparam T the type of the value to write
         * @param value the value to write
         * @throws std::out_of_range if the offset is out of bounds (limit is @link ByteBuffer::_maxCapacity)
         */
        template<typename T>
        void write(const T &value);

        /**
         * @brief Write a value in the buffer at a certain offset, change the writer index (capacity is increased if needed)
         * @tparam T the type of the value to write
         * @param value the value to write
         * @param offset the offset to write the value
         * @throws std::out_of_range if the offset is out of bounds (limit is @link ByteBuffer::_maxCapacity)
         */
        template<typename T>
        void write(const T &value, std::uint32_t offset);

    private:
        std::vector<byte_t> _buffer; /**< The vector to store the bytes */
        std::uint32_t _maxCapacity; /**< The maximum capacity of the buffer */
        std::uint32_t _readPos; /**< The current index of the reader */
        std::uint32_t _writePos; /**< The current index of the writer */
        bool _readOnly; /**< Specify if the ByteBuffer is only readeable */

        /**
         * @brief Ensure that the buffer has enough space to write a certain size
         * @param size the size to check
         */
        inline void ensureCapacity(std::uint32_t size);
    };
} // namespace sa

#endif // SATURNITY_BYTEBUFFER_HPP
