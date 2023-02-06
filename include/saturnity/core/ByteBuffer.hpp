/*
** EPITECH PROJECT, 2023
** ByteBuffer.hpp
** File description:
** ByteBuffer.hpp
*/

#ifndef SATURNITY_BYTEBUFFER_HPP
#define SATURNITY_BYTEBUFFER_HPP

#include <memory>
#include <vector>
#include <exception>

#include "Core.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A byte buffer class to easily, use bytes
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

        //
        // Read methods
        //



        //
        // Write methods
        //

        /**
         * @brief Write a byte in the buffer
         * @param byte the byte to write
         * @throws ReadOnlyException if the ByteBuffer is only readeable
         */
        void writeByte(byte_t byte);

        void writeBytes(const byte_t *bytes, std::uint32_t size);

        void writeBytes(const std::vector<byte_t> &bytes);

        void writeBytes(const ByteBuffer &buffer);

        //
        // Utils methods
        //

        /**
         * @brief Return the vector used as buffer to store bytes
         * @return the vector
         */
        std::vector<byte_t> &vector();

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
        void setWriterIndex(std::size_t writerIndex);

    private:
        std::vector<byte_t> _buffer; /**< The vector to store the bytes */
        std::uint32_t _readPos; /**< The current index of the reader */
        std::uint32_t _writePos; /**< The current index of the writer */
        bool _readOnly; /**< Specify if the ByteBuffer is only readeable */
    };

} // namespace sa

#endif // SATURNITY_BYTEBUFFER_HPP
