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

TEST(ByteBuffer_ReadWrite, varInt)
{
    sa::ByteBuffer buffer;
    buffer.writeVarInt(-128);
    ASSERT_EQ(5, buffer.writerIndex());
    ASSERT_EQ(-128, buffer.readVarInt());
    ASSERT_EQ(5, buffer.readerIndex());

    buffer.writeVarInt(127);
    ASSERT_EQ(6, buffer.writerIndex());
    ASSERT_EQ(127, buffer.readVarInt());
    ASSERT_EQ(6, buffer.readerIndex());
}