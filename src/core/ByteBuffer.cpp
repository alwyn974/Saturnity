/*
** EPITECH PROJECT, 2023
** ByteBuffer.cpp
** File description:
** ByteBuffer.cpp
*/

#include "saturnity/core/ByteBuffer.hpp"

namespace sa {

    ByteBuffer::ByteBuffer(std::uint32_t bufferSize, bool readOnly): _readPos(0), _writePos(0)
    {
        this->_buffer.reserve(bufferSize);
        this->clear();
        this->_readOnly = readOnly;
    }

    ByteBuffer::ByteBuffer(const std::vector<byte_t> &buffer, bool readOnly)
    {
        this->_buffer = buffer;
        this->_readPos = 0;
        this->_writePos = 0;
        this->_readOnly = readOnly;
    }

    ByteBuffer::ByteBuffer(const byte_t *bytes, std::uint32_t size, bool readOnly): _readPos(0), _writePos(0)
    {
        this->_buffer.reserve(size);
        this->clear();
        if (bytes != nullptr) {
            for (std::uint32_t i = 0; i < size; i++)
                this->_buffer.push_back(bytes[i]); //TODO: change to writeBytes method
        }
        this->_readOnly = readOnly;
    }

    void ByteBuffer::clear()
    {
        this->_readPos = 0;
        this->_writePos = 0;
        this->_buffer.clear();
    }

    bool ByteBuffer::isEmpty()
    {
        return this->_buffer.empty();
    }

    std::unique_ptr<ByteBuffer> ByteBuffer::clone()
    {
        auto cloned = std::make_unique<ByteBuffer>(this->_buffer.size());
        for (std::size_t i = 0; i < this->_buffer.size(); i++)
            cloned->_buffer[i] = this->_buffer[i];
        return cloned;
    }

    std::uint32_t ByteBuffer::size() const
    {
        return static_cast<std::uint32_t>(this->_buffer.size());
    }

    void ByteBuffer::resize(std::uint32_t size)
    {
        if (this->_readOnly)
            throw ReadOnlyException("Cannot resize a read only buffer");
        this->_buffer.resize(size);
    }

    bool ByteBuffer::isReadOnly() const
    {
        return this->_readOnly;
    }

    std::uint32_t ByteBuffer::remainingBytes() const
    {
        return this->size() - this->_readPos;
    }

    std::vector<byte_t> &ByteBuffer::vector()
    {
        return this->_buffer;
    }

    bool ByteBuffer::operator==(const ByteBuffer &other) const
    {
        if (this->size() != other.size())
            return false;
        for (std::size_t i = 0; i < this->_buffer.size(); i++)
            if (this->_buffer[i] != other._buffer[i])
                return false;
        return true;
    }

    bool ByteBuffer::operator!=(const ByteBuffer &other) const
    {
        return !(other == *this);
    }

    std::uint32_t ByteBuffer::readerIndex() const
    {
        return this->_readPos;
    }

    void ByteBuffer::setReaderIndex(std::uint32_t readerIndex)
    {
        if (readerIndex >= UINT32_MAX)
            throw std::out_of_range("Reader index is out of bounds: " + std::to_string(readerIndex) + ", maximum is: " + std::to_string(UINT32_MAX));
        this->_readPos = readerIndex;
    }

    std::uint32_t ByteBuffer::writerIndex() const
    {
        return this->_writePos;
    }

    void ByteBuffer::setWriterIndex(size_t writerIndex)
    {
        if (writerIndex >= UINT32_MAX)
            throw std::out_of_range("Writer index is out of bounds: " + std::to_string(writerIndex) + ", maximum is: " + std::to_string(UINT32_MAX));
        this->_writePos = writerIndex;
    }
} // namespace sa
