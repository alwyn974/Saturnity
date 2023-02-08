/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <iostream>
#include <unordered_map>
#include "saturnity/Saturnity.hpp"
#include "saturnity/asio/udp/server.hpp"

class MovePacket : public sa::AbstractPacket {
public:
    int id;
    int x;
    int y;

    explicit MovePacket(int id) : sa::AbstractPacket(sa::AbstractPacket::UDP) {
        this->id = id;
        this->x = x;
        this-> y = y;
    }
    MovePacket() : sa::AbstractPacket(sa::AbstractPacket::UDP) {
    }

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        byteBuffer.writeInt(id);
        byteBuffer.writeInt(x);
        byteBuffer.writeInt(y);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        id = byteBuffer.readInt();
        x = byteBuffer.readInt();
        y = byteBuffer.readInt();
    }
};


class EntitySpawnPacket : public sa::AbstractPacket {
public:
    int id;
    int x;
    int y;

    explicit EntitySpawnPacket(int id, int x, int y) : sa::AbstractPacket(sa::AbstractPacket::UDP) {
        this->id = id;
        this->x = x;
        this-> y = y;
    }
    EntitySpawnPacket() : sa::AbstractPacket(sa::AbstractPacket::UDP) {
    }

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        byteBuffer.writeInt(id);
        byteBuffer.writeInt(x);
        byteBuffer.writeInt(y);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        id = byteBuffer.readInt();
        x = byteBuffer.readInt();
        y = byteBuffer.readInt();
    }
};

