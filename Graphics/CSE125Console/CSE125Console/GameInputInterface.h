#pragma once

#include "stdafx.h"
#include <string>

using namespace std;

class GameInputInterface
{
public:
	bool keyStates[256];
	GameInputInterface();
	~GameInputInterface();
	string name; // store the robot name
	string IPAdress; // store the client IP address

	virtual void VProcessKeyInput(unsigned char key, int x, int y);
	virtual void VProcessSpecialKey(int key, int x, int y);
	virtual void VProcessMouseClick(int button, int state, int x, int y);
	virtual void VProcessPassiveMouse(int x, int y);
	virtual void VProcessMotion(int x, int y);
	virtual void VProcessKeyInputUp(unsigned char key, int x, int y);

};
