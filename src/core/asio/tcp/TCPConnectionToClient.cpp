/*
** EPITECH PROJECT, 2023
** TCPConnectionToClient.cpp
** File description:
** TCPConnectionToClient.cpp
*/

#include "saturnity/asio/tcp/TCPConnectionToClient.hpp"

sa::TCPConnectionToClient::TCPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id) :
    ConnectionToClient(packetRegistry, id, nullptr)
{}

void sa::TCPConnectionToClient::send(sa::ByteBuffer &buffer) {}

void sa::TCPConnectionToClient::disconnect() {}

void sa::TCPConnectionToClient::disconnect(const std::string &reason) {}
