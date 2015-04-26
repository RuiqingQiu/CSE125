#pragma once
#include "stdafx.h"
#include "Shader.h"

#include <stdio.h>
#include "GameView.h"

class HardShadowView:  public GameView
{
public:
	HardShadowView();
	~HardShadowView();
	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have
};

