//
// Created by Quentin on 2/8/2023.
//

#include "client.hpp"

namespace saturnity {

    client::TCP::TCP(const std::string& address, int port) : _socket(_ioContext)
    {
        io::ip::tcp::resolver resolver {_ioContext};
        _endpoints = resolver.resolve(address, std::to_string(port));
    }

    void client::TCP::run() {
        io::async_connect(_socket, _endpoints, [this](boost::system::error_code ec, io::ip::tcp::endpoint ep) {
            if (!ec)
                asyncRead();
        });

        _ioContext.run();
    }

    void client::TCP::stop() {
        boost::system::error_code ec;
        _socket.close(ec);

        if (ec) {
            // process error
        }
    }

    void client::TCP::post(const std::string& message) {
        bool queueIdle = _queue.empty();
        _queue.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void client::TCP::asyncRead() {
        io::async_read(_socket, _streamBuf, io::transfer_at_least(1), [this](boost::system::error_code ec, size_t bytesTransferred) {
            onRead(ec, bytesTransferred);
        });
    }

    void client::TCP::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            stop();
            return;
        }

        std::stringstream message;
        message << std::istream{&_streamBuf}.rdbuf();
        onMessage(message.str());
        asyncRead();
    }

    void client::TCP::asyncWrite() {
        io::async_write(_socket, io::buffer(_queue.front()), [this](boost::system::error_code ec, size_t bytesTransferred) {
            onWrite(ec, bytesTransferred);
        });
    }

    void client::TCP::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            stop();
            return;
        }

        _queue.pop();

        if (!_queue.empty()) {
            asyncWrite();
        }
    }
}