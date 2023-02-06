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
        explicit ByteBuffer(const byte_t *bytes, std::uint32_t size, bool readOnly);

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

        byte_t readByte();

        std::vector<byte_t> readBytes(std::uint32_t size);

        std::vector<byte_t> readBytes(std::uint32_t size, std::uint32_t offset);

        //
        // Write methods
        //

        /**
         * @brief Write a byte in the buffer
         * @param byte the byte to write
         * @throws ReadOnlyException if the ByteBuffer is only readeable
         */
        void writeByte(const byte_t &byte);

        void writeBytes(const ByteBuffer &buffer);

        void writeBytes(const std::vector<byte_t> &bytes);

        void writeBytes(const byte_t *bytes, std::uint32_t size);

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
         * @throws std::out_of_range if the index is out of bounds (limit is UINT32_MAX)
         */
        void setReaderIndex(std::uint32_t readerIndex);

        /**
         * @brief Get the current writer index
         * @return the current index of the writer
         */
        std::uint32_t writerIndex() const;

        /**
         * @brief Set the current writer index
         * @param writerIndex the new index of the writer
         * @throws std::out_of_range if the index is out of bounds (limit is UINT32_MAX)
         */
        void setWriterIndex(std::uint32_t writerIndex);

    protected:
        /**
         * @brief Read a value from the buffer, change the reader index
         * @tparam T the type of the value to read
         * @return the value read
         */
        template<typename T>
        T read();

        /**
         * @brief Read a value from the buffer at a certain offset, don't change the reader index
         * @tparam T the type of the value to read
         * @param offset the offset to read the value
         * @return the value read
         * @throws std::out_of_range if the offset is out of bounds (limit is UINT32_MAX)
         */
        template<typename T>
        T read(std::uint32_t offset);

        /**
         * @brief Write a value in the buffer, change the writer index
         * @tparam T the type of the value to write
         * @param value the value to write
         * @throws std::out_of_range if the offset is out of bounds (limit is UINT32_MAX)
         */
        template<typename T>
        void write(const T &value);

        /**
         * @brief Write a value in the buffer at a certain offset, don't change the writer index
         * @tparam T the type of the value to write
         * @param value the value to write
         * @param offset the offset to write the value
         * @throws std::out_of_range if the offset is out of bounds (limit is UINT32_MAX)
         */
        template<typename T>
        void write(const T &value, std::uint32_t offset);

    private:
        std::vector<byte_t> _buffer; /**< The vector to store the bytes */
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
