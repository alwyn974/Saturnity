/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include "saturnity/Saturnity.hpp"
#include <spdlog/spdlog.h>
#include <iostream>

class MessagePacket : public sa::AbstractPacket {
public:
    MessagePacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};
    explicit MessagePacket(const std::string &message) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP), _message(message) {};

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

    auto server = sa::UDPServer::create(packetRegistry, "0.0.0.0", 2409);
    server->setMaxBufferSize(1024);
    server->onClientConnect = [&](ConnectionToClientPtr &client) {
        spdlog::info("Client asking for connection!");
        return true; // boolean to accept or not the connection
    };
    server->onClientConnected = [&](ConnectionToClientPtr &client) { spdlog::info("Client {} connected!", client->getId()); };
    server->onClientDisconnected = [&](ConnectionToClientPtr &client) { spdlog::info("Client {} disconnected!", client->getId()); };
    server->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
        spdlog::info("Received data from client {}!", client->getId());
    };
    server->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) { spdlog::info("Sent data to client {}!", client->getId()); };

    server->registerHandler<MessagePacket>([&](ConnectionToClientPtr &client, MessagePacket &packet) {
        spdlog::info("Received message from client {}: {}", client->getId(), packet.getMessage());
    });

    server->init();
    try {
        server->start();
    } catch (std::exception &e) {
        spdlog::error("Error while starting server: {}", e.what());
        return 84;
    }
    server->asyncRun();

    const auto packet = std::make_shared<MessagePacket>("Hello world!");

    while (true) {
        server->broadcast(*packet);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
