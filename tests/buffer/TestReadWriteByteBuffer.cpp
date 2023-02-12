/*
** EPITECH PROJECT, 2023
** TestReadWriteByteBuffer.cpp
** File description:
** TestReadWriteByteBuffer.cpp
*/

#include <gtest/gtest.h>
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