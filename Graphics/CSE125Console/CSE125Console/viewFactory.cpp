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
	currentInput = standard_Input;
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
	//hacky quick fix
	buildmode->updateview = false;

	currentView->isCurrentView = false;
	//sky boxes needed for battle mode and console.
	//not needed for menus and build mode
	if (viewmode == viewType::BUILD) {
		helpview->returnTo = viewType::BUILD;
		currentView = buildmode;
		currentInput = gui_Input;
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
		currentInput = gui_Input;
	}
	else if (viewmode == viewType::CONSOLE) {
		currentView = defaultView;
		currentInput = standard_Input;
	}
	currentView->isCurrentView = true;
}

void viewFactory::switchView(unsigned char key) {
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
	buildmode->setDimensions(w, h);
	menumode->setDimensions(w, h);
	helpview->setDimensions(w, h);
	battlemode->setDimensions(w, h);
}

void viewFactory::idleFunc() {
	if (viewmode == viewType::BUILD) {
		viewType s = buildmode->checkTimeOut();
		if (s != viewmode) {
			viewmode = s;
			setView();
		}
	}
}

void viewFactory::mouseFunc(int button, int state, int x, int y) {
	viewType s = currentView->mouseClickFunc(state, x, y);
	if (s != viewmode) {
		viewmode = s;
		setView();
	}
}