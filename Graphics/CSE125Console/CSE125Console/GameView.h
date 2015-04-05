#pragma once
#include "stdafx.h"
#include <vector>
#include "GeoNode.h"
#include "GameInfoPacket.h"
class GameView
{
public:
	GameView();
	~GameView();
	int gameViewId;
	std::vector<GeoNode*> NodeList;

	void OnRender();
	void OnClientUpdate(GameInfoPacket* info);

	void PushGeoNode(GeoNode* node);
	void PopGeoNode(GeoNode* node);
};

