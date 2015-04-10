#pragma once
#include "stdafx.h"
#include <vector>
#include "GeoNode.h"
#include "GameInfoPacket.h"
#include <GL/glut.h>
#include "Camera.h"
#include "Cube.h"
#include "GamePlayer.h"
//#include "GameCore.h"

#ifndef CSE125_GAMEVIEW
#define CSE125_GAMEVIEW
class GameView
{
public:
	GameView();
	~GameView();
	int gameViewId;
	std::vector<GeoNode*> NodeList;
	Camera* pViewCamera;
	GamePlayer* pPlayer;

	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have

	void PushGeoNode(GeoNode* node);
	void PopGeoNode(GeoNode* node);
};

#endif