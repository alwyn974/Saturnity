/*
** EPITECH PROJECT, 2023
** TestConstructorByteBuffer.cpp
** File description:
** TestConstructorByteBuffer.cpp
*/

#include <gtest/gtest.h>
#include "saturnity/core/ByteBuffer.hpp"

TEST(ByteBufferConstructor, DefaultConstructor) {
    sa::ByteBuffer buffer;
    EXPECT_EQ(0, buffer.size());
    EXPECT_EQ(SA_BUFFER_SIZE, buffer.capacity());
    EXPECT_FALSE(buffer.isReadOnly());
    EXPECT_EQ(0, buffer.readerIndex());
    EXPECT_EQ(0, buffer.writerIndex());
    EXPECT_EQ(SA_BUFFER_SIZE, buffer.remainingBytes());
}

TEST(ByteBufferConstructor, BufferSizeConstructor) {
    const std::uint32_t bufferSize = 1024;
    sa::ByteBuffer buffer(bufferSize);
    EXPECT_EQ(0, buffer.size());
    EXPECT_EQ(bufferSize, buffer.capacity());
    EXPECT_FALSE(buffer.isReadOnly());
    EXPECT_EQ(0, buffer.readerIndex());
    EXPECT_EQ(0, buffer.writerIndex());
    EXPECT_EQ(bufferSize, buffer.remainingBytes());
}

TEST(ByteBufferConstructor, VectorConstructor) {
    const std::vector<byte_t> data = {0x01, 0x02, 0x03};
    sa::ByteBuffer buffer(data);
    EXPECT_EQ(data.size(), buffer.size());
    EXPECT_EQ(data.size(), buffer.capacity());
    EXPECT_FALSE(buffer.isReadOnly());
    EXPECT_EQ(data, buffer.getBuffer());
    EXPECT_EQ(0, buffer.readerIndex());
    EXPECT_EQ(data.size(), buffer.writerIndex());
    EXPECT_EQ(data.size(), buffer.remainingBytes());
}

TEST(ByteBufferConstructor, ByteArrayConstructor) {
    const int size = 3;
    const byte_t data[3] = {0x01, 0x02, 0x03};
    sa::ByteBuffer buffer(data, size);
    EXPECT_EQ(sizeof(data), buffer.size());
    EXPECT_EQ(sizeof(data), buffer.capacity());
    EXPECT_FALSE(buffer.isReadOnly());
    for (int i = 0; i < size; i++)
        EXPECT_EQ(data[i], buffer.getBuffer()[i]);
    EXPECT_EQ(0, buffer.readerIndex());
    EXPECT_EQ(3, buffer.writerIndex());
    EXPECT_EQ(size, buffer.remainingBytes());
}

TEST(ByteBufferConstructor, ByteArrayConstructor_ReadOnly)
{
    const int size = 3;
    const byte_t data[3] = {0x01, 0x02, 0x03};
    EXPECT_THROW(sa::ByteBuffer buffer(data, size, true), sa::ByteBuffer::ReadOnlyException);
}

TEST(ByteBufferConstructor, ByteArrayConstructor_NULL)
{
    const int size = 3;
    sa::ByteBuffer buffer(nullptr, size);
    EXPECT_EQ(0, buffer.size());
    EXPECT_EQ(3, buffer.capacity());
    EXPECT_FALSE(buffer.isReadOnly());
    EXPECT_EQ(0, buffer.readerIndex());
    EXPECT_EQ(0, buffer.writerIndex());
    EXPECT_EQ(size, buffer.remainingBytes());
}