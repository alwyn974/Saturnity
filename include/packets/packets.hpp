/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** packets
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <iostream>

namespace saturnity {

    enum field_types
    {
        STRING,
        UNSIGNED_BYTE,
        LONG,
        VARINT,
        BYTE_ARRAY,
        BOOLEAN,
        ARRAY,
        UNDEFINED,
        NONE
    };

    enum state
    {
        HANDSHAKING = 0,
        STATUS,
        LOGIN,
        PLAY
    };

    class IPacketSerializer {
    public:
        virtual void fromBytes(void *) = 0;
        virtual void *toBytes() = 0;
    };

    class Packet : public IPacketSerializer {
    public:
        inline int get_id() { return _packet_id; };
        inline state get_state() { return _state; };
        inline std::string get_field_name() { return _field_name; };
        inline field_types get_field_type() { return _field_type; };
        void fromBytes(void *) override;
        void *toBytes() override;

    private:
        int _packet_id;
        state _state;
        std::string _field_name;
        field_types _field_type;
    };
}  // namespace saturnity::Packets

#endif /* !PACKET_HPP_ */
