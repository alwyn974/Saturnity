/*
** EPITECH PROJECT, 2023
** Saturnity.hpp
** File description:
** Saturnity.hpp
*/

#ifndef SATURNITY_SATURNITY_HPP
#define SATURNITY_SATURNITY_HPP

/**
 * @brief Header file for the Saturnity library. Include all the headers you need.
 * @file Saturnity.hpp
 */

#include "asio/tcp/TCPClient.hpp"
#include "asio/tcp/TCPServer.hpp"
#include "asio/udp/UDPClient.hpp"
#include "asio/udp/UDPServer.hpp"
#include "core/ByteBuffer.hpp"
#include "core/Core.hpp"
#include "core/network/AbstractConnection.hpp"
#include "core/network/client/AbstractClient.hpp"
#include "core/network/client/ConnectionToServer.hpp"
#include "core/network/server/AbstractServer.hpp"
#include "core/network/server/ConnectionToClient.hpp"
#include "core/packet/AbstractPacket.hpp"
#include "core/packet/PacketRegistry.hpp"
#include "core/ThreadSafeQueue.hpp"

#endif // SATURNITY_SATURNITY_HPP
