/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <list>
#include <boost/asio/ip/tcp.hpp>
#include <optional>

#include "packets/packets.hpp"

namespace saturnity {

    enum class IPV {
        V4,
        V6
    };

    namespace asio = boost::asio;
    using boost::asio::ip::tcp;

    namespace server {
        namespace connection {
            class TCP : public std::enable_shared_from_this<TCP> {
            public:
                using Pointer = std::shared_ptr<TCP>;

                static Pointer create(asio::io_context &ioContext) {
                    return Pointer(new TCP(ioContext));
                }

                asio::io_context &getIoContext() const {
                    return _ioContext;
                }

                tcp::socket &socket() {
                    return _socket;
                }

                void start();
                std::string read();
                void write(std::string message);
                void sleepAndWrite(std::string message, int ms);

            private:
                explicit TCP(asio::io_context &ioContext);

            private:
                tcp::socket _socket;
                asio::streambuf _buffer;
                asio::io_context &_ioContext;
                std::unique_ptr<asio::deadline_timer> _timer;
            };
        }

        class TCP {
        public:
            TCP(IPV ipv, unsigned short port);

            void run();

        private:
            void startAccept();

        private:
            IPV _ipVersion;
            unsigned short _port;
            asio::io_context _ioContext;
            tcp::acceptor _acceptor;
            std::vector<connection::TCP::Pointer> _connections{};
        };
    }

}  // namespace saturnity

#endif /* !SERVER_HPP_ */
