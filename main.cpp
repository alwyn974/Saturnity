/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>

#include "saturnity/Saturnity.hpp"

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity!");
    std::vector<byte_t> test = {
        0x1, 0x2
    };
    std::vector<byte_t> copy = test;
    copy[0] = 0x2;

    spdlog::info("{} {} - {}", test[0], copy[0], sizeof(bool));

    sa::ByteBuffer buffer(100);
    buffer.writeByte(0xFF);
    buffer.writeByte(0x00);
    buffer.writeByte(0xEE);
    buffer.writeByte(0x11);

    spdlog::info("{:X}", buffer.readByte());
    spdlog::info("{:X}", buffer.readByte());
    spdlog::info("{:X}", buffer.readByte());
    spdlog::info("{:X}", buffer.readByte());
    spdlog::info("{}", buffer.size());

    return 0;
}
