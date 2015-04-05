#pragma once
#include <string.h>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {

    INIT_CONNECTION = 0,

    ACTION_EVENT = 1,

};

struct Packet {

    unsigned int packet_type;
	unsigned int position_x;
	unsigned int position_y;
	unsigned int position_z;

    void serialize(char * data) {
        memcpy(data, this, sizeof(Packet));
    }

    void deserialize(char * data) {
        memcpy(this, data, sizeof(Packet));
    }
};