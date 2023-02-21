
#include "server.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

namespace saturnity {

    using boost::asio::ip::tcp;

    server::TCP::TCP(IPV ipv, unsigned short port) : _ipVersion(ipv), _port(port), _acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), port)) {

    }

    void server::TCP::run() {
      	std::cout << "Server running" << std::endl;
        try {
            startAccept();
            _ioContext.run();
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void server::TCP::startAccept() {

        _socket.emplace(_ioContext);

        _acceptor.async_accept(*_socket, [this](const boost::system::error_code &ec) {
            auto newConnection = connection::TCP::create(std::move(*_socket));

            if (onJoin) {
                onJoin(newConnection);
            }

            _connections.insert(newConnection);

            if (!ec) {
                newConnection->start(
                    [this](const std::string &message) {
                        if (onClientMessage) {
                            onClientMessage(message);
                        }
                    },
                    [&, weak = std::weak_ptr(newConnection)] {
                        if (auto shared = weak.lock(); shared && _connections.erase(shared)) {
                            if (onLeave) {
                                onLeave(shared);
                            }
                        }
                    }
                );
            }

            startAccept();
        });
    }
    void server::TCP::broadcast(const std::string &message) {
        for (auto &connection : _connections) {
            std::cout << "Broadcasting message to " << connection->getUsername() << std::endl;
            connection->post(message);
        }
    }

    server::connection::TCP::TCP(asio::ip::tcp::socket&& socket) : _socket(std::move(socket)) {
        boost::system::error_code ec;
        std::stringstream name;
        name << _socket.remote_endpoint(ec);
        _username = name.str();
    }

    void server::connection::TCP::start(MessageCallback&& messageCallback, ErrorCallback&& errorCallback) {
        _messageCallback = std::move(messageCallback);
        _errorCallback = std::move(errorCallback);

        asyncRead();
    }

    void server::connection::TCP::post(const std::string &message) {
        bool queueEmpty = _queue.empty();

        _queue.push(message);

        if (queueEmpty) {
            asyncWrite();
        }
    }

    void server::connection::TCP::asyncRead() {
        asio::async_read(_socket, _buffer, asio::transfer_at_least(1), [self = shared_from_this()](const boost::system::error_code ec, std::size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        });
    }

    void server::connection::TCP::onRead(boost::system::error_code ec, std::size_t bytesTransferred) {
        std::cout << "Bytes: " << bytesTransferred << std::endl;
        std::cout << "EC:" << ec.message() << std::endl;
        if (ec) {
            _socket.close(ec);

            _errorCallback();
            return;
        }

        // print buffer data as hexa
        std::cout << "Buffer: ";
        for (auto it = asio::buffers_begin(_buffer.data()); it != asio::buffers_end(_buffer.data()); ++it) {
            std::cout << "0x" << std::hex << (int)(*it) << "(" << (*it) << ") ";
        }
        std::cout << std::endl;

        std::stringstream message;
        message << "Message from " << _username << ": " << std::string(asio::buffers_begin(_buffer.data()), asio::buffers_begin(_buffer.data()) + bytesTransferred);
        _buffer.consume(bytesTransferred);

        _messageCallback(message.str());

        asyncRead();
    }

    void server::connection::TCP::asyncWrite() {
        spdlog::info("Broadcasting: {}", _queue.front());
        asio::async_write(_socket, asio::buffer(_queue.front()), [self = shared_from_this()](const boost::system::error_code ec, std::size_t bytesTransferred) {
            self->onWrite(ec, bytesTransferred);
        });
    }

    void server::connection::TCP::onWrite(boost::system::error_code ec, std::size_t bytesTransferred) {
        if (ec) {
            _socket.close(ec);

            _errorCallback();
            return;
        }

        _queue.pop();

        if (!_queue.empty()) {
            asyncWrite();
        }
    }

}
