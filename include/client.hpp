/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <list>
#include <queue>

#include "packets/packets.hpp"

namespace saturnity {
    namespace io = boost::asio;
    using MessageHandler = std::function<void(std::string)>;

    namespace client {

        class TCP {
        public:
            TCP(const std::string& address, int port);

            void run();
            void stop();
            void post(const std::string& message);

        private:
            void asyncRead();
            void onRead(boost::system::error_code ec, size_t bytesTransferred);
            void asyncWrite();
            void onWrite(boost::system::error_code ec, size_t bytesTransferred);

        public:
            MessageHandler onMessage;

        private:
            io::io_context _ioContext {};
            io::ip::tcp::socket _socket;

            io::ip::tcp::resolver::results_type _endpoints;

            io::streambuf _streamBuf {65536};
            std::queue<std::string> _queue {};
        };
    }
}  // namespace saturnity

#endif /* !CLIENT_HPP_ */
