#include "stdafx.h"
#include "GameInputInterface.h"
#include "GameCore.h"

#pragma once
class StandardGameInput : public GameInputInterface
{
public:
	StandardGameInput();
	~StandardGameInput();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);
	virtual void VProcessSpecialKey(int key, int x, int y);
	virtual void VProcessMouseClick(int button, int state, int x, int y);
	virtual void VProcessPassiveMouse(int x, int y);
	virtual void VProcessMouse(int x, int y);
};

