#pragma once

#include "GameInputInterface.h"
#include "GameCore.h"

class guiGameInput : public GameInputInterface {

public:
	guiGameInput();
	~guiGameInput();

	void VProcessKeyInput(unsigned char key, int x, int y);

	void VProcessMouseClick(int button, int state,int x, int y);
};

