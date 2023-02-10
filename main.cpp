/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>
#include "saturnity/Saturnity.hpp"

class Packet1 : public sa::AbstractPacket {
public:
    Packet1() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};
    void toBytes(sa::ByteBuffer &byteBuffer) override {};
    void fromBytes(sa::ByteBuffer &byteBuffer) override {};
};

class Packet2 : public sa::AbstractPacket {
public:
    Packet2() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};
    void toBytes(sa::ByteBuffer &byteBuffer) override {};
    void fromBytes(sa::ByteBuffer &byteBuffer) override {};
};

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity!");
    spdlog::info("{}", sa::ByteBuffer::getVarShortSize(-4660));

    sa::ByteBuffer buffer(100);
    buffer.writeVarInt(-12);
    std::cout << buffer.writerIndex() << std::endl;
    std::cout << buffer.size() << std::endl;
    std::cout << buffer.readVarInt() << std::endl;
    buffer.writeChar(0x0F);
    buffer.writeChar(0x0F);
    spdlog::info("{} - {} - {} - {}", buffer.size(), buffer.readerIndex(), buffer.writerIndex(), buffer.remainingBytes());
    buffer.clear();
    buffer.writeLong(0x123456789ABCDEF0);
    buffer.writeInt(-12);
    buffer.writeString("Hello World!");
    buffer.writeVarInt(-12);

    spdlog::info("{}", buffer.readLong());
    spdlog::info("{}", buffer.readInt());
    spdlog::info("{}", buffer.readString());
    spdlog::info("{}", buffer.readVarInt());
    spdlog::info("{}", buffer.size());

    sa::PacketRegistry packetRegistry;
    packetRegistry.registerPacket<Packet1>(0x1);
    packetRegistry.registerPacket<Packet2>(0x2);

    return 0;
}
