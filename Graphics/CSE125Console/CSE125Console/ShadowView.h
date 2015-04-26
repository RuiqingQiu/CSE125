#include "stdafx.h"
#include "Shader.h"
#include "GameView.h"



class ShadowView : public GameView
{
public:
	ShadowView();
	~ShadowView();

	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have
};

