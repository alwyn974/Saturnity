/*
** EPITECH PROJECT, 2023
** ByteBuffer.cpp
** File description:
** ByteBuffer.cpp
*/

#include "saturnity/core/ByteBuffer.hpp"

namespace sa {

    ByteBuffer::ByteBuffer(std::uint32_t bufferSize, bool readOnly) : _capacity(bufferSize), _maxCapacity(UINT32_MAX), _readPos(0), _writePos(0)
    {
        this->_buffer.reserve(bufferSize);
        this->clear();
        this->_readOnly = readOnly;
    }

    ByteBuffer::ByteBuffer(const std::vector<byte_t> &buffer, bool readOnly) : _maxCapacity(UINT32_MAX)
    {
        this->_capacity = static_cast<std::uint32_t>(buffer.size());
        this->_buffer = buffer;
        this->_readPos = 0;
        this->_writePos = this->_capacity;
        this->_readOnly = readOnly;
    }

    ByteBuffer::ByteBuffer(const byte_t *bytes, std::uint32_t size, bool readOnly) : _capacity(size), _maxCapacity(UINT32_MAX), _readPos(0), _writePos(0), _readOnly(readOnly)
    {
        this->_buffer.reserve(size);
        this->clear();
        if (bytes != nullptr) this->writeBytes(bytes, size);
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
        for (const byte_t & i : this->_buffer)
            cloned->_buffer.emplace_back(i);
        cloned->setReaderIndex(this->_readPos);
        cloned->setWriterIndex(this->_writePos);
        cloned->_capacity = this->_capacity;
        cloned->_maxCapacity = this->_maxCapacity;
        cloned->_readOnly = this->_readOnly;
        return cloned;
    }

    std::uint32_t ByteBuffer::size() const
    {
        return static_cast<std::uint32_t>(this->_buffer.size());
    }

    std::uint32_t ByteBuffer::capacity() const
    {
        return this->_capacity;
    }

    void ByteBuffer::resize(std::uint32_t size)
    {
        if (this->_readOnly) throw ReadOnlyException("Cannot resize a read only buffer");
        this->_buffer.resize(size);
        this->_capacity = size;
    }

    bool ByteBuffer::isReadOnly() const
    {
        return this->_readOnly;
    }

    std::uint32_t ByteBuffer::remainingBytes() const
    {
        return this->capacity() - this->_readPos;
    }

    bool ByteBuffer::hasSpace(std::uint32_t size) const
    {
        return this->size() + size <= this->capacity();
    }

    void ByteBuffer::replaceAt(std::uint32_t offset, const std::vector<byte_t> &bytes)
    {
        if (this->_readOnly) throw ReadOnlyException("Cannot replace bytes in a read only buffer");
        if (offset > this->size()) throw std::out_of_range(spdlog::fmt_lib::format("Offset is out of bounds: {}, maximum is: {}", offset, this->size()));
        const auto size = static_cast<std::uint32_t>(bytes.size());
        ensureCapacity(offset + size);
        for (std::uint32_t i = 0; i < size; i++) {
            if (offset + i < this->size()) // Ensure that the current vector is big enough, to be overwritten
                this->_buffer[offset + i] = bytes[i];
            else
                this->_buffer.push_back(bytes[i]);
        }
        if (this->_writePos < offset + size) this->_writePos = offset + size;
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
            throw std::out_of_range(spdlog::fmt_lib::format("Offset is out of bounds: {}, maximum is: {}", offset + size, this->size()));
        std::vector<byte_t> bytes;
        bytes.reserve(size);
        for (std::uint32_t i = 0; i < size; i++)
            bytes.push_back(this->_buffer[offset + i]);
        this->_readPos += size;
        return bytes;
    }

    char ByteBuffer::readChar()
    {
        return this->read<char>();
    }

    unsigned char ByteBuffer::readUChar()
    {
        return this->read<unsigned char>();
    }

    bool ByteBuffer::readBoolean()
    {
        return this->read<bool>();
    }

    std::int16_t ByteBuffer::readShort()
    {
        return this->read<std::int16_t>();
    }

    std::uint16_t ByteBuffer::readUShort()
    {
        return this->read<std::uint16_t>();
    }

    std::int32_t ByteBuffer::readInt()
    {
        return this->read<std::int32_t>();
    }

    std::uint32_t ByteBuffer::readUInt()
    {
        return this->read<std::uint32_t>();
    }

    std::int64_t ByteBuffer::readLong()
    {
        return this->read<std::int64_t>();
    }

    std::uint64_t ByteBuffer::readULong()
    {
        return this->read<std::uint64_t>();
    }

    float ByteBuffer::readFloat()
    {
        return this->read<float>();
    }

    double ByteBuffer::readDouble()
    {
        return this->read<double>();
    }

    std::string ByteBuffer::readString()
    {
        const auto size = this->read<std::uint16_t>();
        const auto bytes = this->readBytes(size);
        std::string str(bytes.begin(), bytes.end());
        return str;
    }

    std::int16_t ByteBuffer::readVarShort()
    {
        return static_cast<std::int16_t>(this->readVarUShort());
    }

    std::uint16_t ByteBuffer::readVarUShort()
    {
        std::uint16_t value = 0;
        std::uint32_t position = 0;
        byte_t byte;
        while (true) {
            byte = this->readByte();
            value |= (byte & SEGMENT_BITS) << position;
            if ((byte & CONTINUE_BIT) == 0) break;
            position += 7;
            if (position >= 16) throw VariableLengthTooBigException("VarShort is too big");
        }
        return value;
    }

    std::int32_t ByteBuffer::readVarInt()
    {
        return static_cast<std::int32_t>(this->readVarUInt());
    }

    std::uint32_t ByteBuffer::readVarUInt()
    {
        std::uint32_t value = 0;
        std::uint32_t position = 0;
        byte_t byte;
        while (true) {
            byte = this->readByte();
            value |= (byte & SEGMENT_BITS) << position;
            if ((byte & CONTINUE_BIT) == 0) break;
            position += 7;
            if (position >= 32) throw VariableLengthTooBigException("VarInt is too big");
        }
        return value;
    }

    std::int64_t ByteBuffer::readVarLong()
    {
        return static_cast<std::int64_t>(this->readVarULong());
    }

    std::uint64_t ByteBuffer::readVarULong()
    {
        std::uint64_t value = 0;
        std::uint32_t position = 0;
        byte_t byte;

        while (true) {
            byte = readByte();
            value |= static_cast<std::uint64_t>(byte & SEGMENT_BITS) << position;
            if ((byte & CONTINUE_BIT) == 0) break;
            position += 7;
            if (position >= 64) throw VariableLengthTooBigException("VarLong is too big");
        }

        return value;
    }

    template<typename T>
    T ByteBuffer::read()
    {
        T value = read<T>(this->_readPos);
        return value;
    }

    template<typename T>
    T ByteBuffer::read(std::uint32_t offset)
    {
        const std::size_t size = sizeof(T);
        if (offset + size > this->size())
            throw std::out_of_range(spdlog::fmt_lib::format("Offset is out of bounds: {}, maximum is: {}", offset + size, this->size()));
        T value = *(T *) (&this->_buffer[offset]); // NOLINT
        this->_readPos += size;
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
        if (this->_readOnly) throw ReadOnlyException("Cannot write to a read only buffer");
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

    void ByteBuffer::writeChar(char value)
    {
        this->write<char>(value);
    }

    void ByteBuffer::writeUChar(unsigned char value)
    {
        this->write<unsigned char>(value);
    }

    void ByteBuffer::writeBoolean(bool value)
    {
        this->write<bool>(value);
    }

    void ByteBuffer::writeShort(std::int16_t value)
    {
        this->write<std::int16_t>(value);
    }

    void ByteBuffer::writeUShort(std::uint16_t value)
    {
        this->write<std::uint16_t>(value);
    }

    void ByteBuffer::writeInt(std::int32_t value)
    {
        this->write<std::int32_t>(value);
    }

    void ByteBuffer::writeUInt(std::uint32_t value)
    {
        this->write<std::uint32_t>(value);
    }

    void ByteBuffer::writeLong(std::int64_t value)
    {
        this->write<std::int64_t>(value);
    }

    void ByteBuffer::writeULong(std::uint64_t value)
    {
        this->write<std::uint64_t>(value);
    }

    void ByteBuffer::writeFloat(float value)
    {
        this->write<float>(value);
    }

    void ByteBuffer::writeDouble(double value)
    {
        this->write<double>(value);
    }

    void ByteBuffer::writeString(const std::string &str)
    {
        this->write<std::uint16_t>(static_cast<std::uint16_t>(str.size()));
        const char *cstr = str.c_str();
        const byte_t *bytes = reinterpret_cast<const byte_t *>(cstr); // NOLINT
        this->writeBytes(bytes, static_cast<std::uint32_t>(str.size()));
    }

    void ByteBuffer::writeVarShort(std::int16_t value)
    {
        this->writeUShort(static_cast<std::uint16_t>(value));
    }

    void ByteBuffer::writeVarUShort(std::uint16_t value)
    {
        while (true) {
            uint8_t byte = value & SEGMENT_BITS;
            value >>= 7U;
            if (value != 0) byte |= CONTINUE_BIT;
            writeByte(byte);
            if (value == 0) break;
        }
    }

    void ByteBuffer::writeVarInt(std::int32_t value)
    {
        this->writeVarUInt(static_cast<std::uint32_t>(value));
    }

    void ByteBuffer::writeVarUInt(std::uint32_t value)
    {
        while (true) {
            uint8_t byte = value & SEGMENT_BITS;
            value >>= 7U;
            if (value != 0) byte |= CONTINUE_BIT;
            writeByte(byte);
            if (value == 0) break;
        }
    }

    void ByteBuffer::writeVarLong(std::int64_t value)
    {
        this->writeULong(static_cast<std::uint64_t>(value));
    }

    void ByteBuffer::writeVarULong(std::uint64_t value)
    {
        while (true) {
            uint8_t byte = value & SEGMENT_BITS;
            value >>= 7U;
            if (value != 0) byte |= CONTINUE_BIT;
            writeByte(byte);
            if (value == 0) break;
        }
    }

    template<typename T>
    void ByteBuffer::write(const T &value)
    {
        this->write<T>(value, this->_writePos);
    }

    template<typename T>
    void ByteBuffer::write(const T &value, std::uint32_t offset)
    {
        if (this->_readOnly) throw ReadOnlyException("Cannot write to a read only buffer");
        const std::size_t size = sizeof(T);
        if (offset + size > this->_maxCapacity)
            throw std::out_of_range(
                spdlog::fmt_lib::format("Can't write at offset ({0}), with a size of ({1}), because maximum is: {2}", offset, size, this->_maxCapacity));
        ensureCapacity(offset + size);
        for (std::size_t i = 0; i < size; i++)
            this->_buffer.emplace_back(((byte_t *) &value)[i]); // NOLINT
        this->_writePos += size;
    }

    template<typename T>
    void ByteBuffer::replaceAt(std::uint32_t offset, const T &value)
    {
        if (this->_readOnly) throw ReadOnlyException("Cannot write to a read only buffer");
        const std::size_t size = sizeof(T);
        if (offset > this->_buffer.size())
            throw std::out_of_range(
                spdlog::fmt_lib::format("Can't write at offset ({0}), with a size of ({1}), because maximum is: {2}", offset, size, this->_maxCapacity));
        ensureCapacity(offset + size);
        for (std::size_t i = 0; i < size; i++) {
            byte_t byte = ((byte_t *) &value)[i]; // NOLINT
            if (offset + i < this->size()) // Ensure that the current vector is big enough, to be overwritten
                this->_buffer[offset + i] = byte;
            else
                this->_buffer.push_back(byte);
        }
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
        if (this->size() != other.size()) return false;
        for (std::size_t i = 0; i < this->_buffer.size(); i++)
            if (this->_buffer[i] != other._buffer[i]) return false;
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
        if (readerIndex >= this->size())
            throw std::out_of_range(spdlog::fmt_lib::format("Reader index is out of bounds ({}), maximum is: ({})", readerIndex, this->_capacity));
        this->_readPos = readerIndex;
    }

    void ByteBuffer::resetReaderIndex()
    {
        this->_readPos = 0;
    }

    std::uint32_t ByteBuffer::writerIndex() const
    {
        return this->_writePos;
    }

    void ByteBuffer::setWriterIndex(std::uint32_t writerIndex)
    {
        if (writerIndex >= this->_maxCapacity)
            throw std::out_of_range(spdlog::fmt_lib::format("Writer index is out of bounds ({}), maximum is: ({})", writerIndex, this->_maxCapacity));
        this->_writePos = writerIndex;
    }

    void ByteBuffer::resetWriterIndex()
    {
        this->_writePos = 0;
    }

    int ByteBuffer::getVarShortSize(std::int16_t value)
    {
        if (value < 0) return MAX_VARSHORT_SIZE;
        return getVarUShortSize(value);
    }

    int ByteBuffer::getVarUShortSize(std::uint16_t value)
    {
        for (unsigned int i = 1; i < MAX_VARSHORT_SIZE; i++)
            if ((value & -1U << i * 7) == 0) // NOLINT TODO: fix this
                return static_cast<int>(i);
        return MAX_VARSHORT_SIZE;
    }

    int ByteBuffer::getVarIntSize(std::int32_t value)
    {
        if (value < 0) return MAX_VARINT_SIZE;
        return getVarUIntSize(value);
    }

    int ByteBuffer::getVarUIntSize(std::uint32_t value)
    {
        for (unsigned int i = 1; i < MAX_VARINT_SIZE; i++)
            if ((value & -1U << i * 7) == 0) // NOLINT TODO: fix this
                return static_cast<int>(i);
        return MAX_VARINT_SIZE;
    }

    int ByteBuffer::getVarLongSize(std::int64_t value)
    {
        if (value < 0) return MAX_VARLONG_SIZE;
        return getVarULongSize(value);
    }

    int ByteBuffer::getVarULongSize(std::uint64_t value)
    {
        for (unsigned int i = 1; i < MAX_VARLONG_SIZE; i++)
            if ((value & -1UL << i * 7) == 0L) // NOLINT TODO: fix this
                return static_cast<int>(i);
        return MAX_VARLONG_SIZE;
    }

    void ByteBuffer::ensureCapacity(std::uint32_t size)
    {
        if (size > this->_maxCapacity)
            throw std::out_of_range(spdlog::fmt_lib::format("Cannot ensure capacity: {}, maximum is: {}", size, this->_maxCapacity));
        if (size > this->_capacity) {
            this->_buffer.reserve(size);
            this->_capacity = size;
        }
    }
} // namespace sa
