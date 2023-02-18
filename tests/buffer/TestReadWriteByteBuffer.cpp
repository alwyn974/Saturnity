/*
** EPITECH PROJECT, 2023
** TestReadWriteByteBuffer.cpp
** File description:
** TestReadWriteByteBuffer.cpp
*/

#include <gtest/gtest.h>
#include <random>
#include "saturnity/core/ByteBuffer.hpp"

TEST(ByteBuffer_ReadWrite, byte)
{
    sa::ByteBuffer buffer(100);
    buffer.writeByte(0x012);
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(1, buffer.writerIndex());
    buffer.writeByte(0x0F);
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(2, buffer.writerIndex());
    ASSERT_EQ(0x012, buffer.readByte());
    ASSERT_EQ(0x0F, buffer.readByte());
    ASSERT_EQ(2, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, bytesFromBuffer)
{
    sa::ByteBuffer buffer(100);
    const std::vector<std::uint8_t> bytes = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    buffer.writeBytes(bytes);
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(bytes.size(), buffer.writerIndex());
    sa::ByteBuffer buffer2(100);
    buffer2.writeBytes(buffer);
    ASSERT_EQ(0, buffer2.readerIndex());
    ASSERT_EQ(bytes.size(), buffer2.writerIndex());
    ASSERT_EQ(buffer2.readByte(), 0x01);
    ASSERT_EQ(buffer2.readByte(), 0x02);
    ASSERT_EQ(buffer2.readByte(), 0x03);
    ASSERT_EQ(buffer2.readByte(), 0x04);
    ASSERT_EQ(buffer2.readByte(), 0x05);
    ASSERT_EQ(buffer2.readByte(), 0x06);
    ASSERT_EQ(buffer2.readByte(), 0x07);
    ASSERT_EQ(buffer2.readByte(), 0x08);
    ASSERT_EQ(buffer2.readByte(), 0x09);
    ASSERT_EQ(buffer2.readByte(), 0x0A);
    ASSERT_EQ(bytes.size(), buffer2.readerIndex());
}

TEST(ByteBuffer_ReadWrite, bytesFromVector)
{
    sa::ByteBuffer buffer(100);
    const std::vector<std::uint8_t> bytes = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    buffer.writeBytes(bytes);
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(bytes.size(), buffer.writerIndex());
    ASSERT_EQ(buffer.readByte(), 0x01);
    ASSERT_EQ(buffer.readByte(), 0x02);
    ASSERT_EQ(buffer.readByte(), 0x03);
    ASSERT_EQ(buffer.readByte(), 0x04);
    ASSERT_EQ(buffer.readByte(), 0x05);
    ASSERT_EQ(buffer.readByte(), 0x06);
    ASSERT_EQ(buffer.readByte(), 0x07);
    ASSERT_EQ(buffer.readByte(), 0x08);
    ASSERT_EQ(buffer.readByte(), 0x09);
    ASSERT_EQ(buffer.readByte(), 0x0A);
    ASSERT_EQ(bytes.size(), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, bytesFromCStyleArray)
{
    sa::ByteBuffer buffer(100);
    const std::uint8_t bytes[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    buffer.writeBytes(bytes, 10);
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(10, buffer.writerIndex());
    ASSERT_EQ(buffer.readByte(), 0x01);
    ASSERT_EQ(buffer.readByte(), 0x02);
    ASSERT_EQ(buffer.readByte(), 0x03);
    ASSERT_EQ(buffer.readByte(), 0x04);
    ASSERT_EQ(buffer.readByte(), 0x05);
    ASSERT_EQ(buffer.readByte(), 0x06);
    ASSERT_EQ(buffer.readByte(), 0x07);
    ASSERT_EQ(buffer.readByte(), 0x08);
    ASSERT_EQ(buffer.readByte(), 0x09);
    ASSERT_EQ(buffer.readByte(), 0x0A);
    ASSERT_EQ(10, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, byteMinMax)
{
    sa::ByteBuffer buffer;
    for (int i = 0; i < UINT8_MAX; i++) {
        ASSERT_EQ(i, buffer.writerIndex());
        buffer.writeByte(i);
        ASSERT_EQ(i + 1, buffer.writerIndex());
        ASSERT_EQ(i, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readByte());
        ASSERT_EQ(i + 1, buffer.readerIndex());
    }
    ASSERT_EQ(UINT8_MAX, buffer.writerIndex());
    ASSERT_EQ(UINT8_MAX, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, charMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (char i = INT8_MIN; i < INT8_MAX; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeChar(i);
        ASSERT_EQ(pos + 1, buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readChar());
        pos++;
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(UINT8_MAX, buffer.writerIndex());
    ASSERT_EQ(UINT8_MAX, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, ucharMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (unsigned char i = 0; i < UINT8_MAX; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeUChar(i);
        ASSERT_EQ(pos + 1, buffer.writerIndex());
        ASSERT_EQ(i, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readUChar());
        pos++;
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(UINT8_MAX, buffer.writerIndex());
    ASSERT_EQ(UINT8_MAX, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, boolean)
{
    sa::ByteBuffer buffer;
    ASSERT_EQ(0, buffer.writerIndex());
    buffer.writeBoolean(true);
    ASSERT_EQ(1, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(true, buffer.readBoolean());
    ASSERT_EQ(1, buffer.readerIndex());
    ASSERT_EQ(1, buffer.writerIndex());
    buffer.writeBoolean(false);
    ASSERT_EQ(2, buffer.writerIndex());
    ASSERT_EQ(1, buffer.readerIndex());
    ASSERT_EQ(false, buffer.readBoolean());
    ASSERT_EQ(2, buffer.readerIndex());
    ASSERT_EQ(2, buffer.writerIndex());
}

TEST(ByteBuffer_ReadWrite, shortMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (std::int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeShort(i);
        ASSERT_EQ(pos + sizeof(std::int16_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readShort());
        pos += sizeof(std::int16_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(UINT16_MAX * 2, buffer.writerIndex());
    ASSERT_EQ(UINT16_MAX * 2, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, ushortMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (std::uint16_t i = 0; i < UINT16_MAX; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeUShort(i);
        ASSERT_EQ(pos + sizeof(std::uint16_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readUShort());
        pos += sizeof(std::uint16_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(UINT16_MAX * 2, buffer.writerIndex());
    ASSERT_EQ(UINT16_MAX * 2, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, intMinMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> negativeDistrib(INT32_MIN, -1);
    sa::ByteBuffer buffer;
    int pos = 0;
    for (std::int32_t i = 0; i < 100; i++) {
        std::int32_t value = negativeDistrib(gen);
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeInt(value);
        ASSERT_EQ(pos + sizeof(std::int32_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readInt());
        pos += sizeof(std::int32_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    std::uniform_int_distribution<std::int32_t> positiveDistrib(0, INT32_MAX);
    for (int i = 0; i < 100; i++) {
        std::int32_t value = positiveDistrib(gen);
        ASSERT_EQ(pos, buffer.readerIndex());
        buffer.writeInt(value);
        ASSERT_EQ(pos + sizeof(std::int32_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readInt());
        pos += sizeof(std::int32_t);
        ASSERT_EQ(pos, buffer.writerIndex());
    }

    ASSERT_EQ(200 * sizeof(std::int32_t), buffer.writerIndex());
    ASSERT_EQ(200 * sizeof(std::int32_t), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, uintMinMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> positiveDistrib(0, UINT32_MAX);
    sa::ByteBuffer buffer;
    int pos = 0;
    for (std::uint32_t i = 0; i < 200; i++) {
        std::uint32_t value = positiveDistrib(gen);
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeUInt(value);
        ASSERT_EQ(pos + sizeof(std::uint32_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readUInt());
        pos += sizeof(std::uint32_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(200 * sizeof(std::uint32_t), buffer.writerIndex());
    ASSERT_EQ(200 * sizeof(std::uint32_t), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, longMinMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int64_t> negativeDistrib(INT64_MIN, -1);
    sa::ByteBuffer buffer;
    int pos = 0;
    for (int i = 0; i < 100; i++) {
        std::int64_t value = negativeDistrib(gen);
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeLong(value);
        ASSERT_EQ(pos + sizeof(std::int64_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readLong());
        pos += sizeof(std::int64_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    std::uniform_int_distribution<std::int64_t> positiveDistrib(0, INT32_MAX);
    for (int i = 0; i < 100; i++) {
        std::int64_t value = positiveDistrib(gen);
        ASSERT_EQ(pos, buffer.readerIndex());
        buffer.writeLong(value);
        ASSERT_EQ(pos + sizeof(std::int64_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readLong());
        pos += sizeof(std::int64_t);
        ASSERT_EQ(pos, buffer.writerIndex());
    }

    ASSERT_EQ(200 * sizeof(std::int64_t), buffer.writerIndex());
    ASSERT_EQ(200 * sizeof(std::int64_t), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, ulongMinMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint64_t> positiveDistrib(0, UINT64_MAX);
    sa::ByteBuffer buffer;
    int pos = 0;
    for (std::uint64_t i = 0; i < 200; i++) {
        std::uint64_t value = positiveDistrib(gen);
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeULong(value);
        ASSERT_EQ(pos + sizeof(std::uint64_t), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(value, buffer.readULong());
        pos += sizeof(std::uint64_t);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(200 * sizeof(std::uint64_t), buffer.writerIndex());
    ASSERT_EQ(200 * sizeof(std::uint64_t), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, floatMinMaxOnly)
{
    sa::ByteBuffer buffer;
    buffer.writeFloat(FLT_MAX);
    buffer.writeFloat(FLT_MIN);
    ASSERT_EQ(FLT_MAX, buffer.readFloat());
    ASSERT_EQ(FLT_MIN, buffer.readFloat());
}

TEST(ByteBuffer_ReadWrite, floatMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (int i = -64; i < 64; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeFloat(static_cast<float>(i));
        ASSERT_EQ(pos + sizeof(float), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readFloat());
        pos += sizeof(float);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(128 * sizeof(float), buffer.writerIndex());
    ASSERT_EQ(128 * sizeof(float), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, doubleMinMaxOnly)
{
    sa::ByteBuffer buffer;
    buffer.writeDouble(DBL_MAX);
    buffer.writeDouble(DBL_MIN);
    ASSERT_EQ(DBL_MAX, buffer.readDouble());
    ASSERT_EQ(DBL_MIN, buffer.readDouble());
}

TEST(ByteBuffer_ReadWrite, doubleMinMax)
{
    sa::ByteBuffer buffer;
    int pos = 0;
    for (int i = -64; i < 64; i++) {
        ASSERT_EQ(pos, buffer.writerIndex());
        buffer.writeDouble(i);
        ASSERT_EQ(pos + sizeof(double), buffer.writerIndex());
        ASSERT_EQ(pos, buffer.readerIndex());
        ASSERT_EQ(i, buffer.readDouble());
        pos += sizeof(double);
        ASSERT_EQ(pos, buffer.readerIndex());
    }
    ASSERT_EQ(128 * sizeof(double), buffer.writerIndex());
    ASSERT_EQ(128 * sizeof(double), buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, varShort)
{
    sa::ByteBuffer buffer;
    buffer.writeVarShort(INT8_MIN); // 3 bytes, negative
    ASSERT_EQ(3, buffer.writerIndex());
    ASSERT_EQ(INT8_MIN, buffer.readVarShort());
    ASSERT_EQ(3, buffer.readerIndex());

    buffer.writeVarShort(INT8_MAX); // 1 byte
    ASSERT_EQ(4, buffer.writerIndex());
    ASSERT_EQ(INT8_MAX, buffer.readVarShort());
    ASSERT_EQ(4, buffer.readerIndex());

    buffer.writeVarShort(INT16_MIN); // 3 bytes, negative
    ASSERT_EQ(7, buffer.writerIndex());
    ASSERT_EQ(INT16_MIN, buffer.readVarShort());
    ASSERT_EQ(7, buffer.readerIndex());

    buffer.writeVarShort(INT16_MAX); // 3 bytes max short
    ASSERT_EQ(10, buffer.writerIndex());
    ASSERT_EQ(INT16_MAX, buffer.readVarShort());
    ASSERT_EQ(10, buffer.readerIndex());

    buffer.writeVarShort(256); // 2 bytes
    ASSERT_EQ(12, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarShort());
    ASSERT_EQ(12, buffer.readerIndex());

    buffer.writeVarShort('u'); // 1 byte
    ASSERT_EQ(13, buffer.writerIndex());
    ASSERT_EQ('u', buffer.readVarShort());
    ASSERT_EQ(13, buffer.readerIndex());

    buffer.writeVarShort(0); // 1 byte
    ASSERT_EQ(14, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarShort());

    buffer.writeVarShort(-1); // 3 bytes, negative
    ASSERT_EQ(17, buffer.writerIndex());
    ASSERT_EQ(-1, buffer.readVarShort());
}

TEST(ByteBuffer_ReadWrite, varShortMinMax)
{
    sa::ByteBuffer buffer;
    for (std::int16_t i = INT16_MIN; i < INT16_MAX; i++)
        buffer.writeVarShort(i);
    for (std::int16_t i = INT16_MIN; i < INT16_MAX; i++)
        ASSERT_EQ(i, buffer.readVarShort());
}

TEST(ByteBuffer_ReadWrite, varUShort)
{
    sa::ByteBuffer buffer;
    buffer.writeVarUShort(120); // 1 byte
    ASSERT_EQ(1, buffer.writerIndex());
    ASSERT_EQ(120, buffer.readVarUShort());
    ASSERT_EQ(1, buffer.readerIndex());

    buffer.writeVarUShort(UINT8_MAX); // 2 byte, 255, max => 0b0111'1111 (127)
    ASSERT_EQ(3, buffer.writerIndex());
    ASSERT_EQ(UINT8_MAX, buffer.readVarUShort());
    ASSERT_EQ(3, buffer.readerIndex());

    buffer.writeVarUShort(UINT16_MAX); // 3 bytes
    ASSERT_EQ(6, buffer.writerIndex());
    ASSERT_EQ(UINT16_MAX, buffer.readVarUShort());
    ASSERT_EQ(6, buffer.readerIndex());

    buffer.writeVarUShort(256); // 2 bytes
    ASSERT_EQ(8, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarUShort());
    ASSERT_EQ(8, buffer.readerIndex());

    buffer.writeVarUShort(0); // 1 byte
    ASSERT_EQ(9, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarUShort());
    ASSERT_EQ(9, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, varUShortMinMax)
{
    sa::ByteBuffer buffer;
    for (std::uint16_t i = 0; i < UINT16_MAX; i++)
        buffer.writeVarUShort(i);
    for (std::uint16_t i = 0; i < UINT16_MAX; i++)
        ASSERT_EQ(i, buffer.readVarUShort());
}

TEST(ByteBuffer_ReadWrite, varInt)
{
    sa::ByteBuffer buffer;
    buffer.writeVarInt(INT8_MIN); // 5 bytes, negative
    ASSERT_EQ(5, buffer.writerIndex());
    ASSERT_EQ(INT8_MIN, buffer.readVarInt());
    ASSERT_EQ(5, buffer.readerIndex());

    buffer.writeVarInt(INT8_MAX); // 1 byte
    ASSERT_EQ(6, buffer.writerIndex());
    ASSERT_EQ(INT8_MAX, buffer.readVarInt());
    ASSERT_EQ(6, buffer.readerIndex());

    buffer.writeVarInt(INT16_MIN); // 5 bytes, negative
    ASSERT_EQ(11, buffer.writerIndex());
    ASSERT_EQ(INT16_MIN, buffer.readVarInt());
    ASSERT_EQ(11, buffer.readerIndex());

    buffer.writeVarInt(INT16_MAX); // 3 bytes max short
    ASSERT_EQ(14, buffer.writerIndex());
    ASSERT_EQ(INT16_MAX, buffer.readVarInt());
    ASSERT_EQ(14, buffer.readerIndex());

    buffer.writeVarInt(INT32_MIN); // 5 bytes, negative
    ASSERT_EQ(19, buffer.writerIndex());
    ASSERT_EQ(INT32_MIN, buffer.readVarInt());
    ASSERT_EQ(19, buffer.readerIndex());

    buffer.writeVarInt(INT32_MAX); // 5 bytes max int
    ASSERT_EQ(24, buffer.writerIndex());
    ASSERT_EQ(INT32_MAX, buffer.readVarInt());
    ASSERT_EQ(24, buffer.readerIndex());

    buffer.writeVarInt(256); // 2 bytes
    ASSERT_EQ(26, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarInt());
    ASSERT_EQ(26, buffer.readerIndex());

    buffer.writeVarInt('u'); // 1 byte
    ASSERT_EQ(27, buffer.writerIndex());
    ASSERT_EQ('u', buffer.readVarInt());
    ASSERT_EQ(27, buffer.readerIndex());

    buffer.writeVarInt(0); // 1 byte
    ASSERT_EQ(28, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarInt());
    ASSERT_EQ(28, buffer.readerIndex());

    buffer.writeVarInt(-1); // 5 bytes, negative
    ASSERT_EQ(33, buffer.writerIndex());
    ASSERT_EQ(-1, buffer.readVarInt());
    ASSERT_EQ(33, buffer.readerIndex());

    buffer.writeVarInt(0b1111'1111'1111'1111'1111'1111'1111); // 4 bytes, 268435455
    ASSERT_EQ(37, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111, buffer.readVarInt());
    ASSERT_EQ(37, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, varUInt)
{
    sa::ByteBuffer buffer;
    buffer.writeVarUInt(120); // 1 byte
    ASSERT_EQ(1, buffer.writerIndex());
    ASSERT_EQ(120, buffer.readVarUInt());
    ASSERT_EQ(1, buffer.readerIndex());

    buffer.writeVarUInt(UINT8_MAX); // 2 byte, 255, max => 0b0111'1111 (127)
    ASSERT_EQ(3, buffer.writerIndex());
    ASSERT_EQ(UINT8_MAX, buffer.readVarUInt());
    ASSERT_EQ(3, buffer.readerIndex());

    buffer.writeVarUInt(UINT16_MAX); // 3 bytes
    ASSERT_EQ(6, buffer.writerIndex());
    ASSERT_EQ(UINT16_MAX, buffer.readVarUInt());
    ASSERT_EQ(6, buffer.readerIndex());

    buffer.writeVarUInt(UINT32_MAX); // 5 bytes
    ASSERT_EQ(11, buffer.writerIndex());
    ASSERT_EQ(UINT32_MAX, buffer.readVarUInt());
    ASSERT_EQ(11, buffer.readerIndex());

    buffer.writeVarUInt(256); // 2 bytes
    ASSERT_EQ(13, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarUInt());
    ASSERT_EQ(13, buffer.readerIndex());

    buffer.writeVarUInt(0); // 1 byte
    ASSERT_EQ(14, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarUInt());
    ASSERT_EQ(14, buffer.readerIndex());

    buffer.writeVarUInt(0b1111'1111'1111'1111'1111'1111'1111); // 4 bytes, 268435455
    ASSERT_EQ(18, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111, buffer.readVarUInt());
    ASSERT_EQ(18, buffer.readerIndex());

    buffer.writeVarUInt(0b1111'1111'1111'1111'1111'1111'1111'1111); // 5 bytes, 4294967295
    ASSERT_EQ(23, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarUInt());
    ASSERT_EQ(23, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, varLong)
{
    sa::ByteBuffer buffer;
    buffer.writeVarLong(INT8_MIN); // 10 bytes, negative
    ASSERT_EQ(10, buffer.writerIndex());
    ASSERT_EQ(INT8_MIN, buffer.readVarLong());
    ASSERT_EQ(10, buffer.readerIndex());

    buffer.writeVarLong(INT8_MAX); // 1 byte
    ASSERT_EQ(11, buffer.writerIndex());
    ASSERT_EQ(INT8_MAX, buffer.readVarLong());

    buffer.writeVarLong(INT16_MIN); // 10 bytes, negative
    ASSERT_EQ(21, buffer.writerIndex());
    ASSERT_EQ(INT16_MIN, buffer.readVarLong());
    ASSERT_EQ(21, buffer.readerIndex());

    buffer.writeVarLong(INT16_MAX); // 3 bytes max short
    ASSERT_EQ(24, buffer.writerIndex());
    ASSERT_EQ(INT16_MAX, buffer.readVarLong());

    buffer.writeVarLong(INT32_MIN); // 10 bytes, negative
    ASSERT_EQ(34, buffer.writerIndex());
    ASSERT_EQ(INT32_MIN, buffer.readVarLong());

    buffer.writeVarLong(INT32_MAX); // 5 bytes max int
    ASSERT_EQ(39, buffer.writerIndex());
    ASSERT_EQ(INT32_MAX, buffer.readVarLong());

    buffer.writeVarLong(256); // 2 bytes
    ASSERT_EQ(41, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarLong());
    ASSERT_EQ(41, buffer.readerIndex());

    buffer.writeVarLong('u'); // 1 byte
    ASSERT_EQ(42, buffer.writerIndex());
    ASSERT_EQ('u', buffer.readVarLong());
    ASSERT_EQ(42, buffer.readerIndex());

    buffer.writeVarLong(0); // 1 byte
    ASSERT_EQ(43, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarLong());
    ASSERT_EQ(43, buffer.readerIndex());

    buffer.writeVarLong(-1); // 10 bytes, negative
    ASSERT_EQ(53, buffer.writerIndex());
    ASSERT_EQ(-1, buffer.readVarLong());
    ASSERT_EQ(53, buffer.readerIndex());

    buffer.writeVarLong(0b1111'1111'1111'1111'1111'1111'1111); // 4 bytes, 268435455
    ASSERT_EQ(57, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111, buffer.readVarLong());
    ASSERT_EQ(57, buffer.readerIndex());

    buffer.writeVarLong(0b1111'1111'1111'1111'1111'1111'1111'1111); // 5 bytes, 4294967295
    ASSERT_EQ(62, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarLong());
    ASSERT_EQ(62, buffer.readerIndex());

    buffer.writeVarLong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 6 bytes, 549755813887
    ASSERT_EQ(68, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarLong());
    ASSERT_EQ(68, buffer.readerIndex());

    buffer.writeVarLong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 7 bytes, 70368744177663
    ASSERT_EQ(75, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarLong());
    ASSERT_EQ(75, buffer.readerIndex());

    buffer.writeVarLong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 8 bytes, 9007199254740991
    ASSERT_EQ(83, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarLong());
    ASSERT_EQ(83, buffer.readerIndex());
}

TEST(ByteBuffer_ReadWrite, varULong)
{
    sa::ByteBuffer buffer;
    buffer.writeVarULong(0); // 1 byte
    ASSERT_EQ(1, buffer.writerIndex());
    ASSERT_EQ(0, buffer.readVarULong());
    ASSERT_EQ(1, buffer.readerIndex());

    buffer.writeVarULong(256); // 2 bytes
    ASSERT_EQ(3, buffer.writerIndex());
    ASSERT_EQ(256, buffer.readVarULong());
    ASSERT_EQ(3, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111); // 3 bytes, 65535
    ASSERT_EQ(6, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(6, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111); // 4 bytes, 268435455
    ASSERT_EQ(10, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(10, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111'1111); // 5 bytes, 4294967295
    ASSERT_EQ(15, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(15, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 6 bytes, 549755813887
    ASSERT_EQ(21, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(21, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 7 bytes, 70368744177663
    ASSERT_EQ(28, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(28, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 8 bytes, 9007199254740991
    ASSERT_EQ(36, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(36, buffer.readerIndex());

    buffer.writeVarULong(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111); // 9 bytes, 1152921504606846975
    ASSERT_EQ(45, buffer.writerIndex());
    ASSERT_EQ(0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111, buffer.readVarULong());
    ASSERT_EQ(45, buffer.readerIndex());

    buffer.writeVarULong(UINT64_MAX); // 10 bytes
    ASSERT_EQ(55, buffer.writerIndex());
    ASSERT_EQ(UINT64_MAX, buffer.readVarULong());
    ASSERT_EQ(55, buffer.readerIndex());
}
