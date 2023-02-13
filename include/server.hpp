/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <list>
#include <optional>
#include <queue>
#include <unordered_set>

#include "packets/packets.hpp"

namespace saturnity {

    enum class IPV {
        V4,
        V6
    };

    namespace asio = boost::asio;
    using boost::asio::ip::tcp;

    using MessageCallback = std::function<void(const std::string)>;
    using ErrorCallback = std::function<void()>;

    namespace server {
        namespace connection {
            class TCP : public std::enable_shared_from_this<TCP> {
            public:
                using Pointer = std::shared_ptr<TCP>;

                static Pointer create(asio::ip::tcp::socket&& socket) {
                    return Pointer(new TCP(std::move(socket)));
                }

                inline const std::string &getUsername() const {
                    return _username;
                }

                tcp::socket &socket() {
                    return _socket;
                }

                void start(MessageCallback&& messageCallback, ErrorCallback&& errorCallback);
                void post(const std::string &message);

            private:
                explicit TCP(asio::ip::tcp::socket&& socket);

                void asyncRead();
                void onRead(boost::system::error_code ec, std::size_t bytesTransferred);

                void asyncWrite();
                void onWrite(boost::system::error_code ec, std::size_t bytesTransferred);

            private:
                tcp::socket _socket;
                std::string _username;

                std::queue<std::string> _queue;

                asio::streambuf _buffer {65535};

                MessageCallback _messageCallback;
                ErrorCallback _errorCallback;
            };
        }

        class TCP {
            using OnJoinCallback = std::function<void(connection::TCP::TCP::Pointer)>;
            using OnLeaveCallback = std::function<void(connection::TCP::TCP::Pointer)>;
            using OnClientMessageCallback = std::function<void(const std::string)>;

        public:
            TCP(IPV ipv, unsigned short port);

            void run();
            void broadcast(const std::string &message);

            OnJoinCallback onJoin;
            OnLeaveCallback onLeave;
            OnClientMessageCallback onClientMessage;

        private:
            void startAccept();

        private:
            IPV _ipVersion;
            unsigned short _port;

            asio::io_context _ioContext;
            tcp::acceptor _acceptor;
            std::optional<asio::ip::tcp::socket> _socket;
            std::unordered_set<connection::TCP::Pointer> _connections{};
        };
    }

}  // namespace saturnity

#endif /* !SERVER_HPP_ */
