#pragma once
#include "stdafx.h"
#include <vector>
#include "GeoNode.h"
#include "GameInfoPacket.h"
#include <GL/glut.h>
#include "Camera.h"
#include "Cube.h"

class GameView
{
public:
	GameView();
	~GameView();
	int gameViewId;
	std::vector<GeoNode*> NodeList;
	Camera* pViewCamera;
	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have

	void PushGeoNode(GeoNode* node);
	void PopGeoNode(GeoNode* node);
};

