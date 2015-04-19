#include "stdafx.h"
#include "helpMenu.h"


helpMenu::helpMenu() : gui() {
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h) : gui(w, h) {
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h, viewType r) : gui(w, h) {
	createButtons();
	returnTo = r;
}

helpMenu::~helpMenu()
{
}

void helpMenu::createButtons() {
	backimg = new background("help.jpg", width, height);
	button * back = new button("menuItem/back.jpg", width*0.45, height * 0.1);
	back->setTexture("menuItem/back_sel.jpg", btnState::SELECTED);
	back->setTexture("menuItem/back_press.jpg", btnState::PRESSED);
	back->setScaling(true, true, width, height);

	guiItems.push_back(backimg);
	buttons.push_back(back);
}

viewType helpMenu::mouseClickFunc(int state, int x, int y) {
	//back button
	if (buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP) {
		return returnTo;
	}
	else {
		return viewType::HELP;
	}
}

void helpMenu::VOnRender() {
	gui::VOnRender();
}