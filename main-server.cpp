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

    auto server = sa::UDPServer::create(packetRegistry);
    server->onServerConnected = [&](ConnectionToClientPtr &client) { spdlog::info("Client {} connected!", client->getId()); };
    server->onServerDisconnected = [&](ConnectionToClientPtr &client) { spdlog::info("Client {} disconnected!", client->getId()); };
    server->onServerDataReceived = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
        spdlog::info("Received data from client {}!", client->getId());
    };

    server->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) { spdlog::info("Sent data to client {}!", client->getId()); };

    server->registerHandler<MessagePacket>([&](ConnectionToClientPtr &client, MessagePacket &packet) {
        spdlog::info("Received message from client {}: {}", client->getId(), packet.getMessage());
    });

    const auto packet = std::make_shared<MessagePacket>("Hello world!");

    server->init();
    try {
        server->start();
        std::cout << "Started server!" << std::endl;
    } catch (std::exception &e) {
        spdlog::error("Error while starting server: {}", e.what());
        return 84;
    }

    std::thread t([&]() { server->run(); });
    t.detach();

    while (true) {
        server->broadcast(packet);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        server->sendTo(-1, packet);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
