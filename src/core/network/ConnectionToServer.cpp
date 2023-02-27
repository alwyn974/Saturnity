/*
** EPITECH PROJECT, 2023
** ConnectionToServer.cpp
** File description:
** ConnectionToServer.cpp
*/

#include "saturnity/core/network/client/ConnectionToServer.hpp"
#include "saturnity/core/network/client/AbstractClient.hpp"

namespace sa {
    ConnectionToServer::ConnectionToServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::shared_ptr<AbstractClient> &client) :
        AbstractConnection(packetRegistry),
        _client(client)
    {}

    void ConnectionToServer::disconnect()
    {
        this->_client->disconnect();
    }

    void ConnectionToServer::send(ByteBuffer &buffer)
    {
        this->_client->send(buffer);
    }

    void ConnectionToServer::send(AbstractPacket &packet)
    {
        this->_client->send(packet);
    }

    void ConnectionToServer::send(const std::shared_ptr<AbstractPacket> &packet)
    {
        AbstractConnection::send(packet);
    }

    void ConnectionToServer::send(const std::unique_ptr<AbstractPacket> &packet)
    {
        AbstractConnection::send(packet);
    }
} // namespace sa
