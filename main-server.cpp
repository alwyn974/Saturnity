/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>
#include <unordered_map>
#include "saturnity/Saturnity.hpp"
#include "saturnity/asio/udp/server.hpp"
#include "saturnity/asio/udp/packets/packets.hpp"

std::unordered_map<short, sa::AbstractPacket&> test;


//class KillEntityPacket : public sa::AbstractPacket {
//public:
//    int id;
//    int x;
//    int y;
//
//    explicit EntitySpawnPacket(int id, int x, int y) : sa::AbstractPacket(sa::AbstractPacket::UDP) {
//        this->id = id;
//        this->x = x;
//        this-> y = y;
//    }
//    EntitySpawnPacket() : sa::AbstractPacket(sa::AbstractPacket::UDP) {
//    }
//
//    void toBytes(sa::ByteBuffer &byteBuffer) override {
//        byteBuffer.writeInt(id);
//        byteBuffer.writeInt(x);
//        byteBuffer.writeInt(y);
//    }
//
//    void fromBytes(sa::ByteBuffer &byteBuffer) override {
//        id = byteBuffer.readInt();
//        x = byteBuffer.readInt();
//        y = byteBuffer.readInt();
//    }
//};

void send(sa::AbstractPacket& packet) {
    sa::ByteBuffer buffer(128);
    buffer.writeUShort(0);
    buffer.writeUShort(0);
    packet.toBytes(buffer);
    buffer.setWriterIndex(sizeof(std::uint16_t));
    buffer.writeUShort(buffer.size() - (sizeof(std::uint16_t) * 2));
    buffer.setWriterIndex(buffer.size());
    for (const auto &it: buffer.getBuffer())
        spdlog::info("Byte: {:X}", it);
    buffer.readInt();
    EntitySpawnPacket spawn;
    spawn.fromBytes(buffer);
    spdlog::info("Infos: {}, {}, {}", spawn.id, spawn.x, spawn.y);
}

void send(const std::unique_ptr<sa::AbstractPacket>& packet)
{
    send(*packet);
}

void send(const std::shared_ptr<sa::AbstractPacket>& packet)
{
    send(*packet);
}

int main(int ac, char **av)
{
//    spdlog::info("Welcome to Saturnity Server!");
//    auto factory = PacketFactory::getFactory();
//    factory->registerPacket(0x01, std::make_shared<EntitySpawnPacket>(), [&](auto &buffer){
//        auto packet = std::make_shared<EntitySpawnPacket>();
//        packet->fromBytes(buffer);
//        return packet;
//    });
//    factory->registerPacket(0x02, std::make_shared<MovePacket>(), [&](auto &buffer){
//        auto packet = std::make_shared<MovePacket>();
//        packet->fromBytes(buffer);
//        return packet;
//    });
//
//    for (const auto &[id, packet]: factory->_packetRef) {
//        auto dict = std::dynamic_pointer_cast<EntitySpawnPacket>(packet);
//        std::cout << dict << std::endl;
//        if (dict)
//            spdlog::info("TROP BIEN");
//    }

    boost::asio::io_context ioContext;
    saturnity::UdpServer client(ioContext ,25565);
    ioContext.run();

//EntitySpawnPacket test(0, 40, 40);
//    spdlog::info("{}", sa::ByteBuffer::getVarShortSize(-4660));
//
//    sa::ByteBuffer buffer(100);
//    buffer.writeVarInt(-12);
//    std::cout << buffer.writerIndex() << std::endl;
//    std::cout << buffer.size() << std::endl;
//    std::cout << buffer.readVarInt() << std::endl;
//    buffer.writeChar(0x0F);
//    buffer.writeChar(0x0F);
//    spdlog::info("{} - {} - {} - {}", buffer.size(), buffer.readerIndex(), buffer.writerIndex(), buffer.remainingBytes());
//    buffer.clear();
//    buffer.writeLong(0x123456789ABCDEF0);
//    buffer.writeInt(-12);
//    buffer.writeString("Hello World!");
//    buffer.writeVarInt(-12);
//
//    spdlog::info("{}", buffer.readLong());
//    spdlog::info("{}", buffer.readInt());
//    spdlog::info("{}", buffer.readString());
//    spdlog::info("{}", buffer.readVarInt());
//    spdlog::info("{}", buffer.size());

    return 0;
}
