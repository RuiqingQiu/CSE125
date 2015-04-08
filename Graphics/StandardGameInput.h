#include "stdafx.h"
#include "GameInputInterface.h"
#include "GameCore.h"
#pragma once
class StandardGameInput: public GameInputInterface
{
public:
	StandardGameInput();
	~StandardGameInput();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);

};

