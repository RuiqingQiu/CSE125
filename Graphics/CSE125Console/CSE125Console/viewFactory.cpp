#include "stdafx.h"
#include "viewFactory.h"


viewFactory::viewFactory()
{
	viewmode = viewType::CONSOLE;
	defaultView = new GameView();
	helpview = new helpMenu();
	battlemode = new battleView();
	buildmode = new buildView();
	menumode = new mainMenu();
	currentView = defaultView;

	gui_Input = new guiGameInput();
	standard_Input = new StandardGameInput();
	build_Input = new buildViewInput();
	meunInput = new mainMenuInput();
	currentInput = standard_Input;

	debug = false;
}

viewFactory::viewFactory(int w, int h) {
	viewmode = viewType::CONSOLE;
	defaultView = new GameView();
	helpview = new helpMenu(w, h);
	battlemode = new battleView(w, h);
	buildmode = new buildView(w, h);
	menumode = new mainMenu(w, h);
	currentView = defaultView;

	gui_Input = new guiGameInput();
	standard_Input = new StandardGameInput();
	build_Input = new buildViewInput();
	currentInput = standard_Input;
	meunInput = new mainMenuInput();

	debug = false;
}

viewFactory::viewFactory(bool d) {
	debug = d;
	viewmode = viewType::CONSOLE;
	defaultView = new GameView();
	battlemode = new battleView();

	if (!debug) {
		helpview = new helpMenu();
		buildmode = new buildView();
		menumode = new mainMenu();
		currentView = defaultView;
	}

	gui_Input = new guiGameInput();
	standard_Input = new StandardGameInput();
	meunInput = new mainMenuInput();
	currentInput = standard_Input;
}

viewFactory::~viewFactory()
{
}

/*
GameView * viewFactory::getView() {
	//return currentView;
}
*/
//a gui factory
void viewFactory::setView() {
	if (debug) {
		currentView = defaultView;
		return;
	}

	//hacky quick fix

	
	//hacky quick fix
	if (viewmode != viewType::BUILD) buildmode->updateview = false;
	
	//sky boxes needed for battle mode and console.
	//not needed for menus and build mode
	if (viewmode == viewType::BUILD) {
		helpview->returnTo = viewType::BUILD;
		currentView = buildmode;
		currentInput = build_Input;
	}
	else if (viewmode == viewType::BATTLE) {
		currentView = battlemode;
		currentInput = standard_Input;
	}
	else if (viewmode == viewType::HELP) {
		currentView = helpview;
		currentInput = gui_Input;
	}
	else if (viewmode == viewType::MENU) {
		helpview->returnTo = viewType::MENU;
		currentView = menumode;
		// in menu mode, change ic mainMenuInputmeunInput
		currentInput = meunInput;
	}
	else if (viewmode == viewType::CONSOLE) {
		currentView = defaultView;
		currentInput = standard_Input;
	}
	currentView->isCurrentView = true;
}

void viewFactory::switchView(unsigned char key) {
	if (debug) return;
	switch (key) {
	case '1':
		viewmode = viewType::BUILD;
		break;
	case '2':
		viewmode = viewType::BATTLE;
		break;
	case '3':
		viewmode = viewType::HELP;
		break;
	case '4':
		viewmode = viewType::MENU;
		break;
	case '5':
		viewmode = viewType::CONSOLE;
		break;
	}
	setView();
}

void viewFactory::reshapeFunc(int w, int h) {
	if (debug) return;
	buildmode->setDimensions(w, h);
	menumode->setDimensions(w, h);
	helpview->setDimensions(w, h);
	battlemode->setDimensions(w, h);
}

void viewFactory::idleFunc() {
	//can't check from pGameView, so must do in factory
	//function specific to buildmode
	if (viewmode == viewType::BUILD) {
		viewType s = buildmode->checkTimeOut();
		if (s != viewmode) {
			viewmode = s;
			if (s == viewType::BATTLE) {
				g_pCore->pGamePacketManager->SendRobotBuild(g_pCore->pPlayer->playerid, g_pCore->pGameView->NodeList);
			}
			setView();
		}
	}
}

void viewFactory::keyboardFunc(unsigned char key, int x, int y) {
	//can't check from pGameView, so must do in factory
	//function specific to buildmode
	if (viewmode != viewType::BUILD) return;
	switch (key) {
	case ',':
		buildmode->yRotation -= 90;
		break;
	case '.':
		buildmode->yRotation += 90;
		break;
	default:
		break;
	}
	if (buildmode->yRotation < 0) buildmode->yRotation += 360;
	if (buildmode->yRotation == 360) buildmode->yRotation = 0;
	buildmode->rotateY.makeRotateY(buildmode->yRotation*M_PI / 180.0);
}

void viewFactory::mouseFunc(int button, int state, int x, int y) {
	if (debug) return;
	viewType s = currentView->mouseClickFunc(state, x, y);
	if (s != viewmode) {
		if (viewmode == viewType::BUILD && s == viewType::BATTLE) {
			if (state == GLUT_UP && prevMouseState != GLUT_UP) {
				g_pCore->pGamePacketManager->SendRobotBuild(g_pCore->pPlayer->playerid, g_pCore->pGameView->NodeList);
			}
		}
		viewmode = s;
		setView();
	}
	prevMouseState = state;
}