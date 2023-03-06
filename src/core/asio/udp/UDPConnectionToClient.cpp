/*
** EPITECH PROJECT, 2023
** UDPConnectionToClient.cpp
** File description:
** UDPConnectionToClient.cpp
*/

#include "saturnity/asio/udp/UDPConnectionToClient.hpp"
#include "saturnity/asio/udp/UDPServer.hpp"
#include "saturnity/core/network/server/AbstractServer.hpp"

sa::UDPConnectionToClient::UDPConnectionToClient(
    const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<UDPServer> &server, boost::asio::ip::udp::socket *socket,
    boost::asio::ip::udp::endpoint &clientEndpoint) :
    ConnectionToClient(packetRegistry, id, server, "", 0),
    _udpServer(server),
    _socket(socket)
{
    this->_endpoint = clientEndpoint;
    this->setIp(this->_endpoint.address().to_string());
    this->setPort(this->_endpoint.port());
}

void sa::UDPConnectionToClient::start()
{
    this->connected = true;
}

void sa::UDPConnectionToClient::send(sa::ByteBuffer &buffer)
{
    const bool queueEmpty = this->_sendQueue.empty();
    this->_sendQueue.push(buffer);
    if (queueEmpty) this->asyncSend();
}

void sa::UDPConnectionToClient::send(sa::AbstractPacket &packet)
{
    this->server->sendTo(this->id, packet); // Will call send(ByteBuffer &buffer) on this connection.
}

void sa::UDPConnectionToClient::send(const std::shared_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::UDPConnectionToClient::send(const std::unique_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::UDPConnectionToClient::disconnect()
{
    this->disconnect("");
}

void sa::UDPConnectionToClient::disconnect(const std::string &reason)
{
    this->connected = false;
    if (!reason.empty()) this->server->getLogger().info("Client disconnected for: {}", reason);
    this->_sendQueue.clear();
    this->_udpServer->clientDisconnected(this->shared_from_this());
}

const boost::asio::ip::udp::endpoint &sa::UDPConnectionToClient::getEndpoint() const
{
    return _endpoint;
}

const sa::TSQueue<sa::ByteBuffer> &sa::UDPConnectionToClient::getSendQueue() const
{
    return _sendQueue;
}

void sa::UDPConnectionToClient::asyncSend()
{
    if (this->_sendQueue.empty()) return;
    auto &buffer = this->_sendQueue.front();
    this->_socket->async_send_to(
        boost::asio::buffer(buffer.getBuffer()), this->_endpoint,
        [&buffer, clientPtr = this->shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (!clientPtr->connected) return;
            if (ec) {
                clientPtr->server->getLogger().error("Failed to send data to client ({}): {}", clientPtr->id, ec.message());
                clientPtr->disconnect();
                return;
            }
            if (bytesTransferred != buffer.size()) {
                clientPtr->server->getLogger().warn("Failed to send all data to server: {} bytes sent instead of {}", bytesTransferred, buffer.size());
                return;
            }
            auto client = std::static_pointer_cast<ConnectionToClient>(clientPtr);
            if (clientPtr->server->onServerDataSent) clientPtr->server->onServerDataSent(client, buffer);
            if (!clientPtr->_sendQueue.pop()) clientPtr->server->getLogger().error("Failed to pop from send queue");
            clientPtr->asyncSend();
        });
}
