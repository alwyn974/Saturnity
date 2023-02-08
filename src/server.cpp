
#include "server.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

namespace saturnity {

    using boost::asio::ip::tcp;

    server::TCP::TCP(IPV ipv, unsigned short port) : _ipVersion(ipv), _port(port), _acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), port)) {

    }

    void server::TCP::run() {
        try {
            startAccept();
            _ioContext.run();
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void server::TCP::startAccept() {

        auto newConnection = connection::TCP::create(_ioContext);

        _connections.push_back(newConnection);

        _acceptor.async_accept(newConnection->socket(), [newConnection, this](const boost::system::error_code &ec) {
            if (!ec) {
                std::cout << "Connection accepted" << std::endl;
                newConnection->start();
            } else {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
            startAccept();
        });
    }

    server::connection::TCP::TCP(asio::io_context &ioContext) : _socket(ioContext), _ioContext(ioContext) {


    }

    void server::connection::TCP::start() {
        auto sharedThis = shared_from_this();
        std::string message("Hello from server\n");
        asio::async_write(_socket, asio::buffer(message),
                          [sharedThis](const boost::system::error_code &ec, std::size_t bytesTransferred) {
                              if (!ec) {
                                  std::cout << "Sent " << bytesTransferred << " bytes" << std::endl;
                                  sharedThis->sleepAndWrite("Hello from server\n", 100);
                              } else {
                                  std::cerr << "Error: " << ec.message() << std::endl;
                              }
                          });
    }

    void server::connection::TCP::sleepAndWrite(std::string message, int ms) {
        auto sharedThis = shared_from_this();
        _timer = std::make_unique<boost::asio::deadline_timer>(sharedThis->getIoContext(), boost::posix_time::milliseconds(ms));
        _timer->async_wait([sharedThis, message](const boost::system::error_code &ec) {
            if (!ec) {
                sharedThis->write(message);
            } else {
                std::cerr << "HA: " << ec.message() << std::endl;
            }
        });

    }

    void server::connection::TCP::write(std::string message) {
        auto sharedThis = shared_from_this();
        asio::async_write(_socket, asio::buffer(message),
                          [sharedThis](const boost::system::error_code &ec, std::size_t bytesTransferred) {
                              if (!ec) {
                                  std::cout << "Sent " << bytesTransferred << " bytes" << std::endl;
                                  sharedThis->sleepAndWrite("Hello from server\n", 100);
                              } else {
                                  std::cerr << "Error: " << ec.message() << std::endl;
                              }
                          });
    }

}
