/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>
#include "saturnity/asio/udp/client.hpp"

int main(int ac, char **av)
{
    boost::asio::io_context ioContext;
    std::string address = std::string("10.106.1.160");
    std::string port = std::string("25565");
    saturnity::UdpClient client(address, port, ioContext);
    ioContext.run();
    return 0;
}
