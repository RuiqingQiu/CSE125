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
	void VProcessKeyInput(unsigned char key, int x, int y);

	void VProcessMouseClick(int button, int state, int x, int y);
};

