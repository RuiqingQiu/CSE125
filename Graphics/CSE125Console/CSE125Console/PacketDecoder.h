#pragma once
#include "stdafx.h"
#include "PlayerInfo.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>    // std::min
#include "EventInfo.h"
using namespace std;

class PacketDecoder
{
public:
	PacketDecoder();
	~PacketDecoder();
	static vector<PlayerInfo*> decodePacket(string data);
	static vector<EventInfo*> decodeEvent(string data);

};

