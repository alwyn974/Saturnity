/*
** EPITECH PROJECT, 2023
** ConnectionToClient.cpp
** File description:
** ConnectionToClient.cpp
*/

#include "saturnity/core/network/server/ConnectionToClient.hpp"
#include "saturnity/core/network/server/AbstractServer.hpp"

namespace sa {
    ConnectionToClient::ConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<AbstractServer> &server) :
        AbstractConnection(packetRegistry),
        id(id),
        server(server)
    {
        this->connected = false;
    }

    void ConnectionToClient::start()
    {
        this->connected = true;
    }

    void ConnectionToClient::disconnect()
    {
        this->server->disconnect(this->id);
    }

    void ConnectionToClient::disconnect(const std::string &reason)
    {
        this->server->disconnect(this->id, reason);
    }

    void ConnectionToClient::send(ByteBuffer &buffer)
    {
        this->server->sendTo(this->id, buffer);
    }

    void ConnectionToClient::send(AbstractPacket &packet)
    {
        this->server->sendTo(this->id, packet);
    }

    void ConnectionToClient::send(const std::shared_ptr<AbstractPacket> &packet)
    {
        AbstractConnection::send(packet);
    }

    void ConnectionToClient::send(const std::unique_ptr<AbstractPacket> &packet)
    {
        AbstractConnection::send(packet);
    }

    int ConnectionToClient::getId() const
    {
        return this->id;
    }

    bool ConnectionToClient::isConnected() const
    {
        return connected;
    }

    void ConnectionToClient::setId(int connectionId)
    {
        this->id = connectionId;
    }
} // namespace sa
