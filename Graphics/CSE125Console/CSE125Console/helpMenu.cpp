#include "stdafx.h"
#include "helpMenu.h"


helpMenu::helpMenu() : gui() {
	createButtons();
	returnTo = guiType::MENU;
}

helpMenu::helpMenu(int w, int h) : gui(w, h) {
	createButtons();
	returnTo = guiType::MENU;
}

helpMenu::helpMenu(int w, int h, guiType r) : gui(w, h) {
	createButtons();
	returnTo = r;
}

helpMenu::~helpMenu()
{
}

void helpMenu::createButtons() {
	button * back = new button("menuItem/back.jpg", width*0.5, height * 0.3);
	back->setTexture("menuItem/back_sel.jpg", btnState::SELECTED);
	back->setTexture("menuItem/back_press.jpg", btnState::PRESSED);
	back->setScaling(true, true, width, height);

	buttons.push_back(back);
}

guiType helpMenu::switchClicked(int state, int x, int y) {
	//back button
	if (buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP) {
		return returnTo;
	}
	else {
		return guiType::HELP;
	}
}