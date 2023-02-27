/*
** EPITECH PROJECT, 2023
** AsioConnectionToClient.hpp
** File description:
** AsioConnectionToClient.hpp
*/

#ifndef SATURNITY_ASIOCONNECTIONTOCLIENT_HPP
#define SATURNITY_ASIOCONNECTIONTOCLIENT_HPP

#include "saturnity/core/network/server/ConnectionToClient.hpp"

namespace sa {
    class TCPConnectionToClient : public ConnectionToClient {
    public:
        explicit TCPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id);

        void send(ByteBuffer &buffer) override;

        void disconnect() override;

        void disconnect(const std::string &reason) override;

    private:

    };
}

#endif //SATURNITY_ASIOCONNECTIONTOCLIENT_HPP
