#pragma once
#include "guiGameInput.h"
class buildViewInput : public guiGameInput
{
public:
	buildViewInput();
	~buildViewInput();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);
	virtual void VProcessSpecialKey(int key, int x, int y);
	virtual void VProcessMouseClick(int button, int state, int x, int y);
	virtual void VProcessPassiveMouse(int x, int y);
	virtual void VProcessMotion(int x, int y);

private:
	int prevX;
	int prevY;

	bool leftDown;
	bool rightDown;
};

