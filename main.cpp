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

class MessagePacket : public sa::AbstractPacket {
public:
    MessagePacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};
    explicit MessagePacket(const std::string &message) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP), _message(_message) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeString(this->_message); }

    void fromBytes(sa::ByteBuffer &byteBuffer) override { this->_message = byteBuffer.readString(); }

    std::string getMessage() const { return this->_message; }

private:
    std::string _message;
};

class PacketReceivedEvent {
public:
    explicit PacketReceivedEvent(const std::shared_ptr<sa::AbstractPacket> &packet) : _packet(packet) {};

    template<typename T>
    std::shared_ptr<T> getPacket() const
    {
        return this->_packet;
    }

private:
    std::shared_ptr<sa::AbstractPacket> _packet;
};

class IPacketListener {
public:
    virtual ~IPacketListener() = default;
};

template<typename T, typename = std::enable_if_t<std::is_base_of<IPacketListener, T>::value, T>>
class IPacket {
public:
    virtual ~IPacket() = default;

    virtual void fromBytes(sa::ByteBuffer &byteBuffer) = 0;
    virtual void toBytes(sa::ByteBuffer &byteBuffer) = 0;

    virtual void handle(T &listener) = 0;
};

class EntityAddPacket;

class GameListener : public IPacketListener {
public:
    void handleEntityAddPacket(EntityAddPacket &packet) { spdlog::info("EntityAddPacket"); }
};

class EntityAddPacket : public IPacket<GameListener> {
public:
    void fromBytes(sa::ByteBuffer &byteBuffer) override {}

    void toBytes(sa::ByteBuffer &byteBuffer) override {}

    void handle(GameListener &listener) override { listener.handleEntityAddPacket(*this); }
};

sa::PacketRegistry packetRegistry;

void sendPacket(sa::AbstractPacket &packet)
{
    sa::ByteBuffer byteBuffer(256);
    const uint16_t id = packetRegistry.getPacketId(packet);
    byteBuffer.writeUShort(id);
    byteBuffer.writeUShort(0);
    packet.toBytes(byteBuffer);
    const uint16_t size = byteBuffer.writerIndex();
    byteBuffer.setWriterIndex(sizeof(uint16_t));
    byteBuffer.writeUShort(size - sizeof(uint16_t) * 2); // Skip packet id and size
    byteBuffer.setWriterIndex(size);

    std::cout << typeid(packet).name() << std::endl;
}

void sendPacket(const std::shared_ptr<sa::AbstractPacket> &packet)
{
    sendPacket(*packet);
}

void sendPacket(const std::unique_ptr<sa::AbstractPacket> &packet)
{
    sendPacket(*packet);
}

/*class Test {
public:
    virtual ~Test() = default;

    virtual void needToBeOverrided() = 0;
};

class ChildTest : public Test {
public:
    void needToBeOverrided(const std::string &test) { spdlog::info("Overrided"); }
};*/

int main(int ac, char **av)
{
    /*spdlog::info("Welcome to Saturnity!");
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
*/
    packetRegistry.registerPacket<Packet1>(0x1);
    packetRegistry.registerPacket<Packet2>(0x2);
    packetRegistry.registerPacket<MessagePacket>(0x3);

    sa::ByteBuffer buffer(100);
    buffer.writeString("Hello World!");
    // 0x3

    std::unique_ptr<sa::AbstractPacket> packet = packetRegistry.createPacket(0x3, buffer);
    try {
        packetRegistry.createPacket<MessagePacket>(buffer);
    } catch (std::exception &e) {
        spdlog::error("Error caught: {}", e.what());
    }

    PacketReceivedEvent event(nullptr);
    // event.getPacket<MessagePacket>()->getMessage();
    GameListener listener;
    std::shared_ptr<IPacket<GameListener>> entityAddPacket = std::make_shared<EntityAddPacket>();
    // hmmm
    entityAddPacket->handle(listener);

    sendPacket(std::make_shared<MessagePacket>("Hello World!"));

    return 0;
}
