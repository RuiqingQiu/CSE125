#pragma once

#include "GameInputInterface.h"
#include "GameCore.h"

class guiGameInput : public GameInputInterface {

public:
	guiGameInput();
	~guiGameInput();

	//possible routes for game input:

	//arrow keys to move a selected block (snap to grid/existing bocks)
	//up/down for y
	//left/right for x
	//snapping for z? (force to build from bottom up)

	//mouse rotate of whole robot or <> keys?

	//mouse click of buttons (for sure)
	virtual void VProcessKeyInput(unsigned char key, int x, int y);
	virtual void VProcessSpecialKey(int key, int x, int y);
	virtual void VProcessMouseClick(int button, int state, int x, int y);
	virtual void VProcessPassiveMouse(int x, int y);
	virtual void VProcessMotion(int x, int y);

	virtual void VProcessKeyInputUp(unsigned char key, int x, int y);
};

