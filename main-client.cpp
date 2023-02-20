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
    spdlog::info("Welcome to Saturnity client!");
    auto packetRegistry = std::make_shared<sa::PacketRegistry>();
    packetRegistry->registerPacket<MessagePacket>(0x1);

    auto client = sa::TCPClient::create(packetRegistry);
    client->onClientConnected = [&](ConnectionToServerPtr &server) {
        spdlog::info("Connected to server!");
    };
    client->onClientDisconnected = [&](ConnectionToServerPtr &server) {
        spdlog::info("Disconnected from server!");
    };
    client->onClientDataReceived = [&](ConnectionToServerPtr &server, sa::ByteBuffer &buffer) {
        spdlog::info("Received data from server!");
    };
    client->onClientDataSent = [&](ConnectionToServerPtr &server, sa::ByteBuffer &buffer) {
        spdlog::info("Data sent to server! Bytes: {}", buffer.size());
    };

    bool first = true;
    client->registerHandler<MessagePacket>([&](ConnectionToServerPtr &server, MessagePacket &packet) {
        spdlog::info("Received message from server: {}", packet.getMessage());
        if (first) {
            first = false;
            server->send(std::make_shared<MessagePacket>("Success!"));
        }
    });

    client->init();
    try {
        client->connect("localhost", 2409);
    } catch (const std::exception &e) {
        spdlog::error("Error while connecting to server: {}", e.what());
        return 84;
    }

    auto packet = std::make_shared<MessagePacket>("Hello world!");
    // Time measurement
    auto start = std::chrono::high_resolution_clock::now();
    client->send(packet);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    spdlog::info("Time taken by function: {} microseconds", duration.count());

    while (true) {}

    client->disconnect();
    return 0;
}
