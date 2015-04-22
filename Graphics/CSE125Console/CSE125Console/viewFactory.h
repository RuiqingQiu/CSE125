#pragma once

#include "GameView.h"
#include "helpMenu.h"
#include "buildView.h"
#include "battleView.h"
#include "mainmenu.h"

#include "GameInputInterface.h"
#include "guiGameInput.h"
#include "StandardGameInput.h"
#include "buildViewInput.h"
#include "mainmenuinput.h"

class viewFactory
{
public:
	viewFactory();
	viewFactory(int w, int h);
	viewFactory(bool d);
	~viewFactory();

	bool debug;

	GameView * currentView;

	//view mode determines the mode, changes pGameView
	viewType viewmode;
	//always points to a specific mode, pGameView switches between these
	GameView * defaultView;
	buildView * buildmode;
	mainMenu * menumode;
	helpMenu * helpview;
	battleView * battlemode;

	GameInputInterface * currentInput;
	guiGameInput* gui_Input;
	StandardGameInput* standard_Input;
	guiGameInput * build_Input;
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

private:
	int prevMouseState;
};

