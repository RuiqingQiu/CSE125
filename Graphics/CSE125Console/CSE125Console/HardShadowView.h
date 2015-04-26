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

	int gameViewId;
	std::vector<GeoNode*> NodeList;
	Camera* pViewCamera;
	GamePlayer* pPlayer;
	virtual void VUpdate();

	//node manipulation functions
	virtual void PushGeoNode(GeoNode* node);
	virtual void PopGeoNode(GeoNode* node);
	virtual bool FindGeoNode(GeoNode* node);
	virtual Vector3 translateNode(Vector3 t, GeoNode * node);

	//input functions
	virtual void passiveMouseFunc(int x, int y);
	virtual viewType mouseClickFunc(int state, int x, int y);
	virtual void keyPressFunc(unsigned char key, int x, int y);
	virtual void specialKeyFunc(int key, int x, int y);

	bool isCurrentView;
	GeoNode * currentNode;
};

