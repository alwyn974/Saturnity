/*
** EPITECH PROJECT, 2023
** TestByteBufferUtils.cpp
** File description:
** TestByteBufferUtils.cpp
*/

#include "saturnity/core/ByteBuffer.hpp"
#include <gtest/gtest.h>

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
    ASSERT_EQ(((byte_t *) (&size))[0], buffer.getBuffer()[3]);
    ASSERT_EQ(((byte_t *) (&size))[1], buffer.getBuffer()[4]);
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
    ASSERT_EQ(((byte_t *) (&size))[0], buffer.getBuffer()[3]);
    ASSERT_EQ(((byte_t *) (&size))[1], buffer.getBuffer()[4]);
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

TEST(ByteBuffer_Utils, getVarShortSize)
{
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-32768));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-16384));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-8192));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-4096));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-2048));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-1024));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-512));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-256));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-128));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(-1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarShortSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarShortSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarShortSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarShortSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarShortSize(255));
    ASSERT_EQ(2, sa::ByteBuffer::getVarShortSize(16383));
    ASSERT_EQ(3, sa::ByteBuffer::getVarShortSize(32767));
}

TEST(ByteBuffer_Utils, getVarUShortSize)
{
    ASSERT_EQ(1, sa::ByteBuffer::getVarUShortSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarUShortSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarUShortSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUShortSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUShortSize(255));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUShortSize(16383));
    ASSERT_EQ(3, sa::ByteBuffer::getVarUShortSize(32767));
    ASSERT_EQ(3, sa::ByteBuffer::getVarUShortSize(65535));
}

TEST(ByteBuffer_Utils, getVarIntSize)
{
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-2147483648));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-1073741824));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-536870912));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-268435456));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-134217728));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-67108864));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-33554432));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-16777216));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-8388608));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-4194304));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-2097152));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-1048576));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-524288));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-262144));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-131072));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-65536));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-32768));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-16584));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-8192));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-4096));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-2048));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-1024));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-512));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-256));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-128));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(-1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarIntSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarIntSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarIntSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarIntSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarIntSize(255));
    ASSERT_EQ(2, sa::ByteBuffer::getVarIntSize(16383));
    ASSERT_EQ(3, sa::ByteBuffer::getVarIntSize(32767));
    ASSERT_EQ(3, sa::ByteBuffer::getVarIntSize(65535));
    ASSERT_EQ(4, sa::ByteBuffer::getVarIntSize(8388607));
    ASSERT_EQ(4, sa::ByteBuffer::getVarIntSize(16777215));
    ASSERT_EQ(5, sa::ByteBuffer::getVarIntSize(2147483647));
}

TEST(ByteBuffer_Utils, getVarUIntSize)
{
    ASSERT_EQ(1, sa::ByteBuffer::getVarUIntSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarUIntSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarUIntSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUIntSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUIntSize(255));
    ASSERT_EQ(2, sa::ByteBuffer::getVarUIntSize(16383));
    ASSERT_EQ(3, sa::ByteBuffer::getVarUIntSize(32767));
    ASSERT_EQ(3, sa::ByteBuffer::getVarUIntSize(65535));
    ASSERT_EQ(4, sa::ByteBuffer::getVarUIntSize(8388607));
    ASSERT_EQ(4, sa::ByteBuffer::getVarUIntSize(16777215));
    ASSERT_EQ(5, sa::ByteBuffer::getVarUIntSize(2147483647));
    ASSERT_EQ(5, sa::ByteBuffer::getVarUIntSize(4294967295));
}

TEST(ByteBuffer_Utils, getVarLongSize)
{
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-9223372036854775807));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4611686018427387904));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2305843009213693952));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1152921504606846976));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-576460752303423488));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-288230376151711744));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-144115188075855872));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-72057594037927936));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-36028797018963968));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-18014398509481984));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-9007199254740992));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4503599627370496));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2251799813685248));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1125899906842624));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-562949953421312));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-281474976710656));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-140737488355328));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-70368744177664));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-35184372088832));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-17592186044416));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-8796093022208));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4398046511104));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2199023255552));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1099511627776));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-549755813888));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-274877906944));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-137438953472));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-68719476736));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-34359738368));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-17179869184));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-8589934592));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4294967296));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2147483648));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1073741824));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-536870912));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-268435456));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-134217728));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-67108864));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-33554432));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-16777216));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-8388608));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4194304));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2097152));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1048576));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-524288));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-262144));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-131072));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-65536));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-32768));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-16584));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-8192));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-4096));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-2048));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1024));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-512));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-256));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-128));
    ASSERT_EQ(10, sa::ByteBuffer::getVarLongSize(-1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarLongSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarLongSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarLongSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarLongSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarLongSize(255));
    ASSERT_EQ(3, sa::ByteBuffer::getVarLongSize(32767));
    ASSERT_EQ(3, sa::ByteBuffer::getVarLongSize(65535));
    ASSERT_EQ(4, sa::ByteBuffer::getVarLongSize(8388607));
    ASSERT_EQ(4, sa::ByteBuffer::getVarLongSize(16777215));
    ASSERT_EQ(5, sa::ByteBuffer::getVarLongSize(2147483647));
    ASSERT_EQ(5, sa::ByteBuffer::getVarLongSize(4294967295));
    ASSERT_EQ(6, sa::ByteBuffer::getVarLongSize(549755813887));
    ASSERT_EQ(6, sa::ByteBuffer::getVarLongSize(1099511627775));
    ASSERT_EQ(7, sa::ByteBuffer::getVarLongSize(140737488355327));
    ASSERT_EQ(7, sa::ByteBuffer::getVarLongSize(281474976710655));
    ASSERT_EQ(8, sa::ByteBuffer::getVarLongSize(36028797018963967));
    ASSERT_EQ(8, sa::ByteBuffer::getVarLongSize(72057594037927935));
    ASSERT_EQ(9, sa::ByteBuffer::getVarLongSize(9223372036854775807));
}

TEST(ByteBuffer_Utils, getVarULongSize)
{
    ASSERT_EQ(1, sa::ByteBuffer::getVarULongSize(0));
    ASSERT_EQ(1, sa::ByteBuffer::getVarULongSize(1));
    ASSERT_EQ(1, sa::ByteBuffer::getVarULongSize(127));
    ASSERT_EQ(2, sa::ByteBuffer::getVarULongSize(128));
    ASSERT_EQ(2, sa::ByteBuffer::getVarULongSize(255));
    ASSERT_EQ(3, sa::ByteBuffer::getVarULongSize(32767));
    ASSERT_EQ(3, sa::ByteBuffer::getVarULongSize(65535));
    ASSERT_EQ(4, sa::ByteBuffer::getVarULongSize(8388607));
    ASSERT_EQ(4, sa::ByteBuffer::getVarULongSize(16777215));
    ASSERT_EQ(5, sa::ByteBuffer::getVarULongSize(2147483647));
    ASSERT_EQ(5, sa::ByteBuffer::getVarULongSize(4294967295));
    ASSERT_EQ(6, sa::ByteBuffer::getVarULongSize(549755813887));
    ASSERT_EQ(6, sa::ByteBuffer::getVarULongSize(1099511627775));
    ASSERT_EQ(7, sa::ByteBuffer::getVarULongSize(140737488355327));
    ASSERT_EQ(7, sa::ByteBuffer::getVarULongSize(281474976710655));
    ASSERT_EQ(8, sa::ByteBuffer::getVarULongSize(36028797018963967));
    ASSERT_EQ(8, sa::ByteBuffer::getVarULongSize(72057594037927935));
    ASSERT_EQ(9, sa::ByteBuffer::getVarULongSize(9223372036854775807));
    ASSERT_EQ(10, sa::ByteBuffer::getVarULongSize(UINT64_MAX));
}

TEST(ByteBuffer_Utils, resetWriterIndex)
{
    sa::ByteBuffer buf(10);
    buf.writeByte(1);
    buf.writeByte(2);
    buf.writeByte(3);
    ASSERT_EQ(3, buf.writerIndex());
    buf.resetWriterIndex();
    ASSERT_EQ(0, buf.writerIndex());
}

TEST(ByteBuffer_Utils, resetReaderIndex)
{
    sa::ByteBuffer buf(10);
    buf.writeByte(1);
    buf.writeByte(2);
    buf.writeByte(3);
    ASSERT_EQ(3, buf.writerIndex());
    ASSERT_EQ(0, buf.readerIndex());
    ASSERT_EQ(1, buf.readByte());
    ASSERT_EQ(1, buf.readerIndex());
    ASSERT_EQ(2, buf.readByte());
    ASSERT_EQ(2, buf.readerIndex());
    ASSERT_EQ(3, buf.readByte());
    ASSERT_EQ(3, buf.readerIndex());
    buf.resetReaderIndex();
    ASSERT_EQ(0, buf.readerIndex());
}

TEST(ByteBuffer_Utils, compareBuffer)
{
    sa::ByteBuffer buf1({0x01, 0x02, 0x03});
    sa::ByteBuffer buf2({0x01, 0x02, 0x03});
    ASSERT_TRUE(buf1 == buf2);
    buf2.writeByte(4);
    ASSERT_FALSE(buf1 == buf2);
    ASSERT_TRUE(buf1 != buf2);
}
