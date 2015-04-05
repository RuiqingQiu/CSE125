#pragma once
#include <string.h>
#include <iostream>
#include <vector>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	INIT_CONNECTION = 0,
	GAME_STATE = 1,
	MOVE_LEFT = 2,
	MOVE_RIGHT = 3,
	MOVE_FORWARD = 4,
	MOVE_BACKWARD = 5,
	MOVE_UP = 6,
	MOVE_DOWN = 7,
	ACTION_EVENT = 8
};


struct SPacket {

	unsigned int packet_type;

	char data[MAX_PACKET_SIZE - 4];

	void serialize(char * data) {
		memcpy(data, this, sizeof(SPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(SPacket));
	}
};

struct CPacket {

	unsigned int packet_type;
	char data[1024];

	void serialize(char * data) {
		memcpy(data, this, sizeof(CPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(CPacket));
	}
};