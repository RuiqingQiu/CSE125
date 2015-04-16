#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "gui.h"
#include "GeoNode.h"
#include "SkyBox.h"
#include "GamePacketManager.h"
#include "GamePlayer.h"
#include "GameInputInterface.h"

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

	//changes between the different gui modes
	gui* gameGui;

	//view mode determines the mode 
	guiType viewmode;

	//always points to build mode
	gui * buildmode;
	gui * menumode;
	gui * helpMenu;
	gui * battlemode;

	//add more "static" pointers here
	//always point to main menu
	//always point to battle mode
	//always point to help menu

	//always points to empty gui
	gui * defaultGui;

	//we want a black background/no skybox for buildmode
	//we check the mode and push and pop this node as needed
	GeoNode * skybox;

	//i_pInput switches between these two
	//always points to our gui input
	GameInputInterface* gui_Input;
	//always points to standard input
	GameInputInterface* standard_Input;






};

extern GameCore* g_pCore;

#endif

