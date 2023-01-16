/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "packets/packets.hpp"
#include <list>

namespace saturnity {

    class Server {
    public:
        int createSocket();
        bool handshake();
        void sendPacket(Packet toSend);

        inline std::list<std::string> getPlayerList(){return _playerList;};
        void addPlayer();
        void disconnectPlayer();
        void movePlayer();

    private:
        std::list<std::string> _playerList;
    };
}  // namespace saturnity::Server

#endif /* !SERVER_HPP_ */
