#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "buildView.h"
#include "helpMenu.h"
#include "GeoNode.h"
#include "SkyBox.h"
#include "GamePacketManager.h"
#include "GamePlayer.h"
#include "GameInputInterface.h"
#include "Light.h"
#ifndef CSE125_CORE
#define CSE125_CORE

class GameCore
{
public:
	GameCore();
	~GameCore();

	static float width, height;

	GameView* pGameView;
	GamePacketManager* pGamePacketManager;
	GamePlayer* pPlayer;
	GameInputInterface* i_pInput;


	Light* light;

	//changes between the different gui modes
	gui* gameGui;

	//view mode determines the mode, changes pGameView
	viewType viewmode;

	//always points to a specific mode, pGameView switches between these
	GameView * defaultView;
	buildView * buildmode;
	gui * menumode;
	helpMenu * helpMenu;
	gui * battlemode;

	//we want a black background/no skybox for buildmode
	//we check the mode and push and pop this node as needed
	GeoNode * skybox;

	//i_pInput switches between these two
	//always points to our gui input
	GameInputInterface* gui_Input;
	//always points to standard input
	GameInputInterface* standard_Input;

	//a gui switch 
	void setView();
};

extern GameCore* g_pCore;

#endif

