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
    spdlog::info("Welcome to Saturnity server!");
    auto packetRegistry = std::make_shared<sa::PacketRegistry>();
    packetRegistry->registerPacket<MessagePacket>(0x1);

    auto server = sa::TCPServer(packetRegistry, "0.0.0.0", 2409);
    server.registerHandler<MessagePacket>([&](ConnectionToClientPtr &client, MessagePacket &packet) {
        spdlog::info("Received message from client {}: {}", client->getId(), packet.getMessage());
    });

    server.init();
    server.start();

    const auto packet = std::make_shared<MessagePacket>("Hello world!");

    while (true) {
        server.broadcast(*packet);
    }

    return 0;
}
