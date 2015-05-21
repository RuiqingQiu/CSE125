#pragma once
#include "stdafx.h"
#ifndef __GamePlayer__
#define __GamePlayer__
#include <string>

using namespace std;

class GamePlayer
{
public:
	int playerid;
	std::string name = "Thomas";
	string IPAddress;
	GamePlayer();
	~GamePlayer();
};
#endif

