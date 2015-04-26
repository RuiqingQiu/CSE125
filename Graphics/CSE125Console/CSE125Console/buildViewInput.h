#pragma once
#include "guiGameInput.h"
class buildViewInput : public guiGameInput
{
public:
	buildViewInput();
	~buildViewInput();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);
	virtual void VProcessSpecialKey(int key, int x, int y);
};

