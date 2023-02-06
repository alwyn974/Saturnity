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
        auto cloned = std::make_unique<ByteBuffer>(static_cast<std::uint32_t>(this->_buffer.size()));
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

    bool ByteBuffer::hasSpace(std::uint32_t size) const
    {
        return this->size() + size <= UINT32_MAX;
    }

    //
    // Read
    //

    byte_t ByteBuffer::readByte()
    {
        return this->read<byte_t>();
    }

    std::vector<byte_t> ByteBuffer::readBytes(std::uint32_t size)
    {
        return this->readBytes(size, this->_readPos);
    }

    std::vector<byte_t> ByteBuffer::readBytes(std::uint32_t size, std::uint32_t offset)
    {
        if (offset + size > this->size())
            throw std::out_of_range("Offset is out of bounds: " + std::to_string(offset) + ", maximum is: " + std::to_string(this->size()));
        std::vector<byte_t> bytes;
        bytes.reserve(size);
        for (std::uint32_t i = 0; i < size; i++)
            bytes.push_back(this->_buffer[offset + i]);
        this->_readPos += size;
    }

    template<typename T>
    T ByteBuffer::read()
    {
        T value = read<T>(this->_readPos);
        this->_readPos += sizeof(T);
        return value;
    }

    template<typename T>
    T ByteBuffer::read(std::uint32_t offset)
    {
        if (offset + sizeof(T) > this->size())
            throw std::out_of_range("Offset is out of bounds: " + std::to_string(offset) + ", maximum is: " + std::to_string(this->size()));
        T value = *(T *)(&this->_buffer[offset]); // NOLINT
        return value;
    }

    //
    // Write
    //

    void ByteBuffer::writeByte(const byte_t &byte)
    {
        this->write<byte_t>(byte);
    }

    void ByteBuffer::writeBytes(const byte_t *bytes, std::uint32_t size)
    {
        if (this->_readOnly)
            throw ReadOnlyException("Cannot write to a read only buffer");
        ensureCapacity(this->_writePos + size);
        for (std::uint32_t i = 0; i < size; i++)
            this->_buffer.emplace_back(bytes[i]);
        this->_writePos += size;
    }

    void ByteBuffer::writeBytes(const std::vector<byte_t> &bytes)
    {
        this->writeBytes(bytes.data(), static_cast<std::uint32_t>(bytes.size()));
    }

    void ByteBuffer::writeBytes(const ByteBuffer &buffer)
    {
        this->writeBytes(buffer.getBuffer());
    }

    template<typename T>
    void ByteBuffer::write(const T &value)
    {
        this->write<T>(value, this->_writePos);
        this->_writePos += sizeof(T);
    }

    template<typename T>
    void ByteBuffer::write(const T &value, std::uint32_t offset)
    {
        if (this->_readOnly)
            throw ReadOnlyException("Cannot write to a read only buffer");
        ensureCapacity(offset + sizeof(T));
        for (std::size_t i = 0; i < sizeof(T); i++)
            this->_buffer.emplace_back(((byte_t *) &value)[i]); // NOLINT
    }

    std::vector<byte_t> &ByteBuffer::vector()
    {
        return this->_buffer;
    }

    const std::vector<byte_t> &ByteBuffer::getBuffer() const
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

    void ByteBuffer::setWriterIndex(std::uint32_t writerIndex)
    {
        if (writerIndex >= UINT32_MAX)
            throw std::out_of_range("Writer index is out of bounds: " + std::to_string(writerIndex) + ", maximum is: " + std::to_string(UINT32_MAX));
        this->_writePos = writerIndex;
    }

    void ByteBuffer::ensureCapacity(std::uint32_t size)
    {
        if (this->size() + size > UINT32_MAX)
            throw std::out_of_range("Cannot ensure capacity: " + std::to_string(size) + ", maximum is: " + std::to_string(UINT32_MAX));
        this->_buffer.reserve(this->size() + size);
    }
} // namespace sa
