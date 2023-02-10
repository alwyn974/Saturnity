/*
** EPITECH PROJECT, 2023
** TestByteBuffer.cpp
** File description:
** TestByteBuffer.cpp
*/

#include <gtest/gtest.h>
#include "saturnity/core/ByteBuffer.hpp"

TEST(ByteBuffer, writeByte)
{
    sa::ByteBuffer buffer(100);
    buffer.writeByte(0x0F);

    ASSERT_EQ(buffer.readByte(), 0x0F);
}

TEST(ByteBuffer, writeChar)
{
    sa::ByteBuffer buffer(100);
    buffer.writeChar(0x0F);

    ASSERT_EQ(buffer.readChar(), 0x0F);
}

TEST(ByteBuffer, writeShort)
{
    sa::ByteBuffer buffer(100);
    buffer.writeShort(0x0F);

    ASSERT_EQ(buffer.readShort(), 0x0F);
}

TEST(ByteBuffer, writeInt)
{
    sa::ByteBuffer buffer(100);
    buffer.writeInt(0x0F);

    ASSERT_EQ(buffer.readInt(), 0x0F);
}

TEST(ByteBuffer, writeLong)
{
    sa::ByteBuffer buffer(100);
    buffer.writeLong(0x0F);

    ASSERT_EQ(buffer.readLong(), 0x0F);
}

TEST(ByteBuffer, writeFloat)
{
    sa::ByteBuffer buffer(100);
    buffer.writeFloat(0.0F);

    ASSERT_EQ(buffer.readFloat(), 0.0F);
}

TEST(ByteBuffer, writeDouble)
{
    sa::ByteBuffer buffer(100);
    buffer.writeDouble(0.0);

    ASSERT_EQ(buffer.readDouble(), 0.0);
}

TEST(ByteBuffer, writeString)
{
    sa::ByteBuffer buffer(100);
    buffer.writeString("Hello World!");

    ASSERT_EQ(buffer.readString(), "Hello World!");
}

TEST(ByteBuffer, writeVarInt)
{
    sa::ByteBuffer buffer(100);
    buffer.writeVarInt(-12);

    ASSERT_EQ(buffer.readVarInt(), -12);
}

TEST(ByteBuffer, writeVarShort)
{
    sa::ByteBuffer buffer(100);
    buffer.writeVarShort(-4660);

    ASSERT_EQ(buffer.readVarShort(), -4660);
}

TEST(ByteBuffer, writeVarLong)
{
    sa::ByteBuffer buffer(100);
    buffer.writeVarLong(-4660);

    ASSERT_EQ(buffer.readVarLong(), -4660);
}

TEST(ByteBuffer, writeBytes)
{
    sa::ByteBuffer buffer(100);
    buffer.writeBytes({0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC});

    const std::vector<byte_t> bytes = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC};
    ASSERT_EQ(buffer.readBytes(12), bytes);
}

TEST(ByteBuffer, writeBytesWithCStyleArray)
{
    sa::ByteBuffer buffer(100);
    const byte_t bytes[12] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC};
    buffer.writeBytes(bytes, 12);

    const std::vector<byte_t> bytesVector = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC};
    ASSERT_EQ(buffer.readBytes(12), bytesVector);
}
