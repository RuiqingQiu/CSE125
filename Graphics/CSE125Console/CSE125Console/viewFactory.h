#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "helpMenu.h"
#include "buildView.h"
#include "battleView.h"
#include "mainmenu.h"
#include "endView.h"

#include "GameInputInterface.h"
#include "guiGameInput.h"
#include "StandardGameInput.h"
#include "buildViewInput.h"
#include "mainmenuinput.h"

#include "scoreBox.h"
#include "loadDisplay.h"

#include <ctime>

class viewFactory
{
public:
	viewFactory();
	viewFactory(int w, int h);
	viewFactory(bool d);
	~viewFactory();

	//bool debug = true;

	GameView * currentView;

	//view mode determines the mode, changes pGameView
	viewType viewmode;
	//always points to a specific mode, pGameView switches between these
	GameView * defaultView;
	buildView * buildmode;
	mainMenu * menumode;
	helpMenu * helpview;
	battleView * battlemode;
	endView * gameOver;

	GameInputInterface * currentInput;
	guiGameInput* gui_Input;
	StandardGameInput* standard_Input;
	buildViewInput * build_Input;
	mainMenuInput* meunInput; // add menu input

	//getters
	//GameView * getView();
	//GameInputInterface * getInput();

	//set view
	void setView();

	void switchView(unsigned char key);
	void reshapeFunc(int w, int h);
	void idleFunc();
	void mouseFunc(int button, int state, int x, int y);
	void keyboardFunc(unsigned char key, int x, int y);

	void delayedRebuild();

	//one scorebox for whole game
	scoreBox * score;
	loadDisplay * loading;
	bool loadingBattle = true;

private:
	int prevMouseState;

	std::clock_t start;
	bool delay;

	float duration = -1;
};

