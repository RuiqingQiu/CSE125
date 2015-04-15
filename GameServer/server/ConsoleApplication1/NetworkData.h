#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include "GameObj.h"
#include "definition.h"


#define MAX_PACKET_SIZE 1000000

//NetworkData.h

struct CPacket {

	unsigned int packet_type;
	//char data[1024];
	char data[10000];


	void serialize(char * data) {
		memcpy(data, this, sizeof(CPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(CPacket));
	}
};

struct SPacket {

	unsigned int packet_type;
	char data[10000];

	void serialize(char * data) {
		memcpy(data, this, sizeof(SPacket));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(SPacket));
	}
};
