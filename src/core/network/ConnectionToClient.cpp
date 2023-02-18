/*
** EPITECH PROJECT, 2023
** ConnectionToClient.cpp
** File description:
** ConnectionToClient.cpp
*/

#include "saturnity/core/network/ConnectionToClient.hpp"
#include "saturnity/core/network/AbstractServer.hpp"

namespace sa {
    ConnectionToClient::ConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id) : AbstractConnection(packetRegistry), _id(id) {}

    int ConnectionToClient::getId() const
    {
        return this->_id;
    }

    void ConnectionToClient::disconnect()
    {
        this->_server->disconnect(this->_id);
    }

    void ConnectionToClient::disconnect(const std::string &reason)
    {
        this->_server->disconnect(this->_id, reason);
    }

    void ConnectionToClient::send(ByteBuffer &buffer)
    {
        this->_server->sendTo(this->_id, buffer);
    }

    void ConnectionToClient::send(AbstractPacket &packet)
    {
        this->_server->sendTo(this->_id, packet);
    }
} // namespace sa
