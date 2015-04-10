#pragma once
#include "stdafx.h"
#include <vector>
#include "GeoNode.h"
#include "GameInfoPacket.h"
#include <GL/glut.h>
#include "Camera.h"
#include "Cube.h"
<<<<<<< HEAD
#include "GamePlayer.h"
//#include "GameCore.h"

#ifndef CSE125_GAMEVIEW
#define CSE125_GAMEVIEW
=======

>>>>>>> e29dfd8afdf19e5348c40766ae46614a91611c5d
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
