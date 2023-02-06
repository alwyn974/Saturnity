/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <iostream>

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
    buffer.writeLong(0x123456789ABCDEF0);
    buffer.writeInt(-12);
    buffer.writeString("Hello World!");
    buffer.writeVarInt(-12);
    /*buffer.writeByte(0xFF);
    buffer.writeByte(0x00);
    buffer.writeByte(0xEE);
    buffer.writeByte(0x11);*/

    /*auto buf = boost::asio::buffer(buffer.getBuffer());
    auto byteBuf = boost::asio::buffer_cast<const byte_t *>(buf);
    sa::ByteBuffer byteBuffer(byteBuf, buf.size());

    std::vector<byte_t>  toto = buffer.readBytes(8); // NOLINT
    std::int64_t ehoh = 0;
    std::memcpy(&ehoh, toto.data(), 8);
    std::cout << ehoh << std::endl;*/

    spdlog::info("{}", buffer.readLong());
    spdlog::info("{}", buffer.readInt());
    spdlog::info("{}", buffer.readString());
    spdlog::info("{}", buffer.readVarInt());
    spdlog::info("{}", buffer.size());

    return 0;
}
