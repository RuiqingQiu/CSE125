#pragma once
#include "stdafx.h"
#include "PlayerInfo.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>    // std::min
using namespace std;

class PacketDecoder
{
public:
	PacketDecoder();
	~PacketDecoder();
	static vector<PlayerInfo*> decodePacket(string data);
};

