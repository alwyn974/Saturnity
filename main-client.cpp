/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>
#include "saturnity/Saturnity.hpp"

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

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity client!");
    auto packetRegistry = std::make_shared<sa::PacketRegistry>();
    packetRegistry->registerPacket<MessagePacket>(0x1);

    auto client = sa::TCPClient(packetRegistry);
    client.registerHandler<MessagePacket>([&](ConnectionToServerPtr &server, MessagePacket &packet) {
        spdlog::info("Received message from server: {}", packet.getMessage());
    });

    client.connect("localhost", 2409);

    auto packet = std::make_shared<MessagePacket>("Hello world!");
    client.send(packet);

    while (true)
        ;

    return 0;
}
