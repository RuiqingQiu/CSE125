#pragma once
#include "stdafx.h"
#include "Shader.h"
#include <vector>
#include "GeoNode.h"
#include "GameInfoPacket.h"
#include <GL/glut.h>
#include "Camera.h"
#include "Cube.h"
#include "GamePlayer.h"
#include "Plane.h"
#include "Model3DFactory.h"

#ifndef CSE125_GAMEVIEW
#define CSE125_GAMEVIEW

enum class viewType {
	BUILD,
	BATTLE,
	HELP,
	MENU,
	CONSOLE
};

class GameView
{
public:
	GameView();
	~GameView();
	int gameViewId;
	std::vector<GeoNode*> NodeList;
	std::vector<GeoNode*> NodeListBuffer;

	Camera* pViewCamera;
	GamePlayer* pPlayer;

	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have
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

#endif