#pragma once
#include <string.h>
#include <iostream>
#include <vector>

#define MAX_PACKET_SIZE 1000000

//NetworkData.h
enum PacketTypes {
	INIT_CONNECTION = 0,
	GAME_STATE = 1,
	MOVE_LEFT = 2,
	MOVE_RIGHT = 3,
	MOVE_FORWARD = 4,
	MOVE_BACKWARD = 5,
	MOVE_UP = 6,
	MOVE_DOWN = 7,
	INIT_CLIENT = 8,
	CONFIRM_CONNECTION = 9,
	BUILD_ROBOT = 10,
	SHOOT = 11,
	INIT_BUILD = 12,
	TIMER = 13,
	BUILD_REQUEST = 14,
};

struct CPacket {

	unsigned int packet_type;
	char data[5000];
	void serialize(char * data) {
		memcpy(data, this, sizeof(CPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(CPacket));
	}
};

struct SPacket {

	unsigned int packet_type;

	char data[50000];

	void serialize(char * data) {
		memcpy(data, this, sizeof(SPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(SPacket));
	}
};