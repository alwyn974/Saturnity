/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>

#include "saturnity/Saturnity.hpp"

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity!");
    sa::ByteBuffer buffer(100);
    buffer.writeVarInt(-12);
    std::cout << buffer.writerIndex() << std::endl;
    std::cout << buffer.size() << std::endl;
    std::cout << buffer.readVarInt() << std::endl;
    buffer.writeChar(0x0F);
    buffer.writeChar(0x0F);
    spdlog::info("{} - {} - {} - {}", buffer.size(), buffer.readerIndex(), buffer.writerIndex(), buffer.remainingBytes());
    buffer.clear();
    buffer.writeLong(0x123456789ABCDEF0);
    buffer.writeInt(-12);
    buffer.writeString("Hello World!");
    buffer.writeVarInt(-12);

    spdlog::info("{}", buffer.readLong());
    spdlog::info("{}", buffer.readInt());
    spdlog::info("{}", buffer.readString());
    spdlog::info("{}", buffer.readVarInt());
    spdlog::info("{}", buffer.size());

    return 0;
}
