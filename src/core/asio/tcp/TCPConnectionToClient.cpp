/*
** EPITECH PROJECT, 2023
** TCPConnectionToClient.cpp
** File description:
** TCPConnectionToClient.cpp
*/

#include "saturnity/asio/tcp/TCPConnectionToClient.hpp"
#include "saturnity/asio/tcp/TCPServer.hpp"
#include "saturnity/core/network/server/AbstractServer.hpp"

sa::TCPConnectionToClient::TCPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<TCPServer> &server, boost::asio::ip::tcp::socket socket) :
    ConnectionToClient(packetRegistry, id, server),
    _tcpServer(server),
    _socket(std::move(socket))
{
    this->_endpoint = this->_socket.remote_endpoint();
    this->connected = this->_socket.is_open();
}

void sa::TCPConnectionToClient::start()
{
    this->asyncReadPacketHeader();
}

void sa::TCPConnectionToClient::send(sa::ByteBuffer &buffer)
{
    const bool queueEmpty = this->_sendQueue.empty();
    this->_sendQueue.push(buffer);
    if (queueEmpty) this->asyncSend();
}

void sa::TCPConnectionToClient::send(sa::AbstractPacket &packet)
{
    this->server->sendTo(this->id, packet); // Will call send(ByteBuffer &buffer) on this connection.
}

void sa::TCPConnectionToClient::send(const std::shared_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::TCPConnectionToClient::send(const std::unique_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::TCPConnectionToClient::disconnect()
{
    this->disconnect("");
}

void sa::TCPConnectionToClient::disconnect(const std::string &reason)
{
    boost::system::error_code ec;
    this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    if (ec) this->server->getLogger().error("Error when trying to disconnect client: {}", ec.message());
    this->_socket.close(ec);
    if (ec) this->server->getLogger().error("Error when trying to close client: {}", ec.message());
    this->connected = false;
    if (!reason.empty()) this->server->getLogger().info("Client disconnected for: {}", reason);
    this->_sendQueue.clear();
    this->_tcpServer->clientDisconnected(this->shared_from_this());
}

const boost::asio::ip::tcp::socket &sa::TCPConnectionToClient::getSocket() const
{
    return _socket;
}

const boost::asio::ip::tcp::endpoint &sa::TCPConnectionToClient::getEndpoint() const
{
    return _endpoint;
}

const sa::TSQueue<sa::ByteBuffer> &sa::TCPConnectionToClient::getSendQueue() const
{
    return _sendQueue;
}

void sa::TCPConnectionToClient::asyncSend()
{
    if (this->_sendQueue.empty()) return;
    auto &buffer = this->_sendQueue.front();
    this->_socket.async_send(boost::asio::buffer(buffer.getBuffer()), [this, &buffer, clientPtr = this->shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred) {
        if (ec) {
            this->server->getLogger().error("Failed to send data to client ({}): {}", this->id, ec.message());
            this->disconnect();
            return;
        }
        if (bytesTransferred != buffer.size()) {
            this->server->getLogger().warn("Failed to send all data to server: {} bytes sent instead of {}", bytesTransferred, buffer.size());
            return;
        }
        auto client = std::static_pointer_cast<ConnectionToClient>(clientPtr);
        if (this->server->onServerDataSent) this->server->onServerDataSent(client, buffer);
        if (!this->_sendQueue.pop()) this->server->getLogger().error("Failed to pop from send queue");
        this->asyncSend();
    });
}

void sa::TCPConnectionToClient::asyncReadPacketHeader()
{
    auto header = std::shared_ptr<byte_t>(new byte_t[AbstractPacket::HEADER_SIZE], std::default_delete<byte_t[]>()); // NOLINT
    this->_socket.async_read_some(
        boost::asio::buffer(header.get(), AbstractPacket::HEADER_SIZE), [this, header](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->server->getLogger().error("Failed to read packet header from client ({}): {}", this->getId(), ec.message());
                this->disconnect();
                return;
            }
            if (bytesTransferred == 0) return this->asyncReadPacketHeader();
            if (bytesTransferred != AbstractPacket::HEADER_SIZE) {
                this->server->getLogger().error("Failed to read packet header from client ({}): {} bytes read instead of {}", this->getId(), bytesTransferred, AbstractPacket::HEADER_SIZE);
                return this->asyncReadPacketHeader();
            }
            std::uint16_t packetId = 0, packetSize = 0;
            std::memcpy(&packetId, header.get(), sizeof(std::uint16_t));
            std::memcpy(&packetSize, header.get() + sizeof(std::uint16_t), sizeof(std::uint16_t));
            if (packetId == 0 || packetSize == 0) {
                this->server->getLogger().warn("Failed to read packet header from client ({}): packetId or packetSize is 0", this->getId());
                return this->asyncReadPacketHeader();
            }
            this->asyncReadPacketBody(packetId, packetSize);
        });
}

void sa::TCPConnectionToClient::asyncReadPacketBody(std::uint16_t packetId, std::uint16_t packetSize)
{
    this->server->getLogger().info("Reading packet {} body of size {}", packetId, packetSize);
    auto body = std::shared_ptr<byte_t>(new byte_t[packetSize], std::default_delete<byte_t[]>()); // NOLINT
    this->_socket.async_read_some(
        boost::asio::buffer(body.get(), packetSize), [this, packetSize, packetId, body, clientPtr = this->shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->server->getLogger().error("Failed to read packet body from server: {}", ec.message());
                this->disconnect();
                return;
            }
            if (bytesTransferred != packetSize) {
                this->server->getLogger().error("Failed to read packet body from server: {} bytes read instead of {}", bytesTransferred, packetSize);
                this->disconnect();
                return;
            }
            this->server->getLogger().info("Received packet {} of size {}", packetId, packetSize);
            auto buffer = ByteBuffer(body.get(), packetSize);
            auto client = std::static_pointer_cast<ConnectionToClient>(clientPtr);
            if (this->server->onServerDataReceived) this->server->onServerDataReceived(client, packetId,packetSize, buffer);
            this->_tcpServer->clientSentPacket(clientPtr, packetId, buffer);
            this->asyncReadPacketHeader();
        });
}
