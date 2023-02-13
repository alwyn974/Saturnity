/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include "client.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    saturnity::client::TCP client {"localhost", 4242};

    client.onMessage = [](const std::string& message) { std::cout << message; };

    std::thread t {[&client]() { client.run(); }};

    while (true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.post(message);
    }

    client.stop();
    t.join();
    return 0;
}