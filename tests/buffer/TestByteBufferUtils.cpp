/*
** EPITECH PROJECT, 2023
** TestByteBufferUtils.cpp
** File description:
** TestByteBufferUtils.cpp
*/

#include <gtest/gtest.h>
#include "saturnity/core/ByteBuffer.hpp"

TEST(ByteBuffer_Utils, isEmpty)
{
    sa::ByteBuffer buffer(100);
    ASSERT_TRUE(buffer.isEmpty());
    buffer.writeChar(0x0F);
    ASSERT_FALSE(buffer.isEmpty());
}

TEST(ByteBuffer_Utils, clear)
{
    sa::ByteBuffer buffer(100);
    buffer.writeChar(0x0F);
    buffer.clear();
    ASSERT_TRUE(buffer.isEmpty());
    ASSERT_EQ(0, buffer.size());
    ASSERT_EQ(0, buffer.readerIndex());
    ASSERT_EQ(0, buffer.writerIndex());
    ASSERT_EQ(100, buffer.capacity());
    ASSERT_EQ(100, buffer.remainingBytes());
    ASSERT_TRUE(buffer.getBuffer().empty());
}

TEST(ByteBuffer_Utils, clone)
{
    sa::ByteBuffer buffer(100);
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    auto clone = buffer.clone();
    ASSERT_EQ(buffer.size(), clone->size());
    ASSERT_EQ(buffer.readerIndex(), clone->readerIndex());
    ASSERT_EQ(buffer.writerIndex(), clone->writerIndex());
    ASSERT_EQ(buffer.remainingBytes(), clone->remainingBytes());
    ASSERT_EQ(buffer.readChar(), clone->readChar());
    ASSERT_EQ(buffer.readChar(), clone->readChar());
    ASSERT_EQ(buffer.readChar(), clone->readChar());
    ASSERT_EQ(buffer.readString(), clone->readString());
}

TEST(ByteBuffer_Utils, capacity)
{
    sa::ByteBuffer buffer(100);
    ASSERT_EQ(100, buffer.capacity());
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_EQ(100, buffer.capacity());
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_EQ(100, buffer.capacity());
}

TEST(ByteBuffer_Utils, ensureCapacity)
{
    sa::ByteBuffer buffer(0);
    ASSERT_EQ(0, buffer.capacity());
    buffer.writeChar('a');
    ASSERT_EQ(1, buffer.capacity());
    buffer.writeChar('l');
    ASSERT_EQ(2, buffer.capacity());
    buffer.writeChar('w');
    ASSERT_EQ(3, buffer.capacity());
    buffer.writeString("yn");
    ASSERT_EQ(7, buffer.capacity());
}

TEST(ByteBuffer_Utils, resize)
{
    sa::ByteBuffer buffer(100);
    ASSERT_EQ(100, buffer.capacity());
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    buffer.resize(200);
    ASSERT_EQ(200, buffer.capacity());
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_EQ(200, buffer.capacity());
}

TEST(ByteBuffer_Utils, resizeReadOnly)
{
    sa::ByteBuffer buffer(100, true);
    ASSERT_EQ(100, buffer.capacity());
    ASSERT_THROW(buffer.resize(200), sa::ByteBuffer::ReadOnlyException);
}

TEST(ByteBuffer_Utils, isReadOnly)
{
    sa::ByteBuffer buffer(100);
    ASSERT_FALSE(buffer.isReadOnly());
    sa::ByteBuffer buffer2(100, true);
    ASSERT_TRUE(buffer2.isReadOnly());
}

TEST(ByteBuffer_Utils, getBuffer)
{
    sa::ByteBuffer buffer(100);
    ASSERT_EQ(100, buffer.capacity());
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_EQ(7, buffer.size());
    ASSERT_EQ(7, buffer.getBuffer().size());
    ASSERT_EQ('a', buffer.getBuffer()[0]);
    ASSERT_EQ('l', buffer.getBuffer()[1]);
    ASSERT_EQ('w', buffer.getBuffer()[2]);
    std::uint16_t size = 2;
    ASSERT_EQ(((byte_t *)(&size))[0], buffer.getBuffer()[3]);
    ASSERT_EQ(((byte_t *)(&size))[1], buffer.getBuffer()[4]);
    ASSERT_EQ('y', buffer.getBuffer()[5]);
    ASSERT_EQ('n', buffer.getBuffer()[6]);
}

TEST(ByteBuffer_Utils, hasSpace)
{
    sa::ByteBuffer buffer(100);
    ASSERT_TRUE(buffer.hasSpace(100));
    ASSERT_TRUE(buffer.hasSpace(50));
    ASSERT_TRUE(buffer.hasSpace(1));
    ASSERT_FALSE(buffer.hasSpace(101));
    ASSERT_FALSE(buffer.hasSpace(200));
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_FALSE(buffer.hasSpace(100));
    ASSERT_TRUE(buffer.hasSpace(50));
    ASSERT_TRUE(buffer.hasSpace(1));
    ASSERT_FALSE(buffer.hasSpace(101));
    ASSERT_FALSE(buffer.hasSpace(200));
}

TEST(ByteBuffer_Utils, replaceAt)
{
    sa::ByteBuffer buffer(100);
    buffer.writeChar('a');
    buffer.writeChar('l');
    buffer.writeChar('w');
    buffer.writeString("yn");
    ASSERT_EQ(7, buffer.size());
    ASSERT_EQ(7, buffer.getBuffer().size());
    ASSERT_EQ('a', buffer.getBuffer()[0]);
    ASSERT_EQ('l', buffer.getBuffer()[1]);
    ASSERT_EQ('w', buffer.getBuffer()[2]);
    std::uint16_t size = 2;
    ASSERT_EQ(((byte_t *)(&size))[0], buffer.getBuffer()[3]);
    ASSERT_EQ(((byte_t *)(&size))[1], buffer.getBuffer()[4]);
    ASSERT_EQ('y', buffer.getBuffer()[5]);
    ASSERT_EQ('n', buffer.getBuffer()[6]);
    buffer.replaceAt(0, {'b'});
    buffer.replaceAt(1, {'o'});
    buffer.replaceAt(2, {'o'});
    buffer.replaceAt(3, {'b'});
    buffer.replaceAt(4, {'a'});
    buffer.replaceAt(5, {'r'});
    buffer.replaceAt(6, {'!'});
    ASSERT_EQ(7, buffer.size());
    ASSERT_EQ(7, buffer.getBuffer().size());
    ASSERT_EQ('b', buffer.getBuffer()[0]);
    ASSERT_EQ('o', buffer.getBuffer()[1]);
    ASSERT_EQ('o', buffer.getBuffer()[2]);
    ASSERT_EQ('b', buffer.getBuffer()[3]);
    ASSERT_EQ('a', buffer.getBuffer()[4]);
    ASSERT_EQ('r', buffer.getBuffer()[5]);
    ASSERT_EQ('!', buffer.getBuffer()[6]);
}