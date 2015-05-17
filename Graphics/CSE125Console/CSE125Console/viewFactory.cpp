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

	score = new scoreBox(0, 0, 200, 100, true, false);
	battlemode->addItem(score);
	buildmode->addItem(score);

	debug = false;
}

viewFactory::viewFactory(int w, int h) {
	cout << "view factory loading" << endl;
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

	score = new scoreBox(20, h - 110, 200, 100, true, false);
	battlemode->addItem(score);
	buildmode->addItem(score);

	debug = false;
	cout << "view factory loading done" << endl;

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

	//hacky quick fix for being able to switch console modes with number keys
	//if (viewmode != viewType::BUILD) buildmode->updateview = false;
	currentView->isCurrentView = false;
	currentView->VUpdate();
	
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
		setView();
		break;
	case '2':
		viewmode = viewType::BATTLE;
		setView();
		break;
	case '3':
		viewmode = viewType::HELP;
		setView();
		break;
	case '4':
		viewmode = viewType::MENU;
		setView();
		break;
	case '5':
		viewmode = viewType::CONSOLE;
		setView();
		break;
	default:
		break;
	}
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
	if (key == '6') {
		//score->updateScore(1, 0, 0);
	}
	else if (key == '7') {
		//score->updateScore(0, 1, 0);
	}
	else if(key == '8') {
		//score->updateScore(0, 0, 1);
	}

	if (viewmode != viewType::BUILD) return;
	switch (key) {
	case ',':
		buildmode->rotateRobot(-90);
		break;
	case '.':
		buildmode->rotateRobot(90);
		break;
	default:
		break;
	}
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