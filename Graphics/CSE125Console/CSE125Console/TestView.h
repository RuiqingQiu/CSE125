#pragma once
#include "stdafx.h"
#include "Shader.h"

#include <stdio.h>
#include "GameView.h"

class TestView : public GameView
{
public:
	TestView();
	~TestView();
	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have
};

