/*
** EPITECH PROJECT, 2023
** TestPacketRegistry.cpp
** File description:
** TestPacketRegistry.cpp
*/

#include <gtest/gtest.h>
#include "saturnity/core/packet/PacketRegistry.hpp"

class HelloPacket : public sa::AbstractPacket {
public:
    HelloPacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};
    explicit HelloPacket(const std::string &message) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), _message(message) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeString(this->_message); }

    void fromBytes(sa::ByteBuffer &byteBuffer) override { this->_message = byteBuffer.readString(); }

    std::string getMessage() const { return this->_message; }

private:
    std::string _message;
};

struct EntityMovePacket : public sa::AbstractPacket {
    int id, x, y;
    EntityMovePacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), id(-1), x(0), y(0) {};
    explicit EntityMovePacket(int id, int x, int y) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), id(id), x(x), y(y) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override
    {
        byteBuffer.writeInt(this->id);
        byteBuffer.writeInt(this->x);
        byteBuffer.writeInt(this->y);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override
    {
        this->id = byteBuffer.readInt();
        this->x = byteBuffer.readInt();
        this->y = byteBuffer.readInt();
    }
};

struct EntityKillPacket : public sa::AbstractPacket {
    int id;
    EntityKillPacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), id(-1) {};
    explicit EntityKillPacket(int id) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), id(id) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeInt(this->id); }

    void fromBytes(sa::ByteBuffer &byteBuffer) override { this->id = byteBuffer.readInt(); }
};

struct NopePacket : public sa::AbstractPacket {
    NopePacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeInt(0); }

    void fromBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.readInt(); }
};

struct NoEmptyConstructorPacket : public sa::AbstractPacket {
    int id;
    explicit NoEmptyConstructorPacket(int id) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP), id(id) {};

    void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeInt(this->id); }

    void fromBytes(sa::ByteBuffer &byteBuffer) override { this->id = byteBuffer.readInt(); }
};

TEST(PacketRegistry, SimpleRegister)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    packetRegistry.getPacketId<HelloPacket>();
    ASSERT_EQ(packetRegistry.getPacketId<HelloPacket>(), 0);
    ASSERT_EQ(packetRegistry.getPacketId<EntityMovePacket>(), 1);
    ASSERT_EQ(packetRegistry.getPacketId<EntityKillPacket>(), 2);

    ASSERT_TRUE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityKillPacket>());
    ASSERT_FALSE(packetRegistry.hasPacket<NopePacket>());
}

TEST(PacketRegistry, RegisterWithSameId)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_THROW(packetRegistry.registerPacket<NopePacket>(0), sa::PacketRegistry::PacketAlreadyRegisteredException);
}

TEST(PacketRegistry, RegisterWithSameType)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_THROW(packetRegistry.registerPacket<HelloPacket>(3), sa::PacketRegistry::PacketAlreadyRegisteredException);
}

TEST(PacketRegistry, RegisterWithSameIdAndType)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_THROW(packetRegistry.registerPacket<HelloPacket>(0), sa::PacketRegistry::PacketAlreadyRegisteredException);
}

TEST(PacketRegistry, MissingEmptyConstructor)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    // ASSERT_THROW(packetRegistry.registerPacket<NoEmptyConstructorPacket>(3), sa::PacketRegistry::PacketMissingEmptyConstructorException);
}

TEST(PacketRegistry, hasPacket)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_TRUE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityKillPacket>());
    ASSERT_FALSE(packetRegistry.hasPacket<NopePacket>());

    HelloPacket helloPacket("Hello");
    EntityMovePacket entityMovePacket(1, 2, 3);
    EntityKillPacket entityKillPacket(1);

    ASSERT_TRUE(packetRegistry.hasPacket(helloPacket));
    ASSERT_TRUE(packetRegistry.hasPacket(entityMovePacket));
    ASSERT_TRUE(packetRegistry.hasPacket(entityKillPacket));

    ASSERT_TRUE(packetRegistry.hasPacket(0));
    ASSERT_TRUE(packetRegistry.hasPacket(1));
    ASSERT_TRUE(packetRegistry.hasPacket(2));
}

TEST(PacketRegistry, createPacket)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);

    sa::ByteBuffer byteBuffer;
    byteBuffer.writeString("Hello");

    std::unique_ptr<sa::AbstractPacket> helloPacket = packetRegistry.createPacket(0, byteBuffer);
    EXPECT_NO_THROW(dynamic_cast<HelloPacket &>(*helloPacket));
    EXPECT_THROW(dynamic_cast<EntityMovePacket &>(*helloPacket), std::bad_cast);

    ASSERT_EQ(dynamic_cast<HelloPacket &>(*helloPacket).getMessage(), "Hello");

    ASSERT_THROW(packetRegistry.createPacket(1, byteBuffer), sa::PacketRegistry::PacketNotRegisteredException);

    byteBuffer.resetReaderIndex();
    auto packet = packetRegistry.createPacket<HelloPacket>(byteBuffer);
    ASSERT_EQ(packet->getMessage(), "Hello");
}

TEST(PacketRegistry, createPacketWithWrongType)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);

    sa::ByteBuffer byteBuffer;
    byteBuffer.writeString("Hello");

    ASSERT_THROW(packetRegistry.createPacket<EntityMovePacket>(byteBuffer), sa::PacketRegistry::PacketNotRegisteredException);
}

TEST(PacketRegistry, getPacketId)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_EQ(packetRegistry.getPacketId<HelloPacket>(), 0);
    ASSERT_EQ(packetRegistry.getPacketId<EntityMovePacket>(), 1);
    ASSERT_EQ(packetRegistry.getPacketId<EntityKillPacket>(), 2);

    HelloPacket helloPacket("Hello");
    EntityMovePacket entityMovePacket(1, 2, 3);
    EntityKillPacket entityKillPacket(1);

    ASSERT_EQ(packetRegistry.getPacketId(helloPacket), 0);
    ASSERT_EQ(packetRegistry.getPacketId(entityMovePacket), 1);
    ASSERT_EQ(packetRegistry.getPacketId(entityKillPacket), 2);
}

TEST(PacketRegistry, unregisterPacket)
{
    sa::PacketRegistry packetRegistry;

    packetRegistry.registerPacket<HelloPacket>(0);
    packetRegistry.registerPacket<EntityMovePacket>(1);
    packetRegistry.registerPacket<EntityKillPacket>(2);

    ASSERT_TRUE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityKillPacket>());

    packetRegistry.unregisterPacket<HelloPacket>();

    ASSERT_FALSE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityKillPacket>());

    packetRegistry.unregisterPacket<EntityMovePacket>();

    ASSERT_FALSE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_FALSE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_TRUE(packetRegistry.hasPacket<EntityKillPacket>());

    packetRegistry.unregisterPacket<EntityKillPacket>();

    ASSERT_FALSE(packetRegistry.hasPacket<HelloPacket>());
    ASSERT_FALSE(packetRegistry.hasPacket<EntityMovePacket>());
    ASSERT_FALSE(packetRegistry.hasPacket<EntityKillPacket>());
}
