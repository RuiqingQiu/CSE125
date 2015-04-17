#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu() : gui() {
	createButtons();
}

mainMenu::mainMenu(int w, int h) : gui(w, h) {
	createButtons();
}

mainMenu::~mainMenu(){

}

void mainMenu::createButtons() {

	button * robo = new button("menuItem/enterRobotName.jpg", width*0.2, height*0.5, 300, 70);
	robo->setScaling(true, true, width, height);
	
	button * play = new button("menuItem/play.jpg", width*0.5, height*0.4);
	play->setTexture("menuItem/play_sel.jpg", btnState::SELECTED);
	play->setTexture("menuItem/play_press.jpg", btnState::PRESSED);
	play->setScaling(true, true, width, height);

	button * help = new button("menuItem/help.jpg", width*0.5, height * 0.3);
	help->setTexture("menuItem/help_sel.jpg", btnState::SELECTED);
	help->setTexture("menuItem/help_press.jpg", btnState::PRESSED);
	help->setScaling(true, true, width, height);

	buttons.push_back(robo);
	buttons.push_back(play);
	buttons.push_back(help);
}


void mainMenu::VOnRender(){
	gui::VOnRender();
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info){

}

void mainMenu::onClick(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height - y);
	}
}

guiType mainMenu::switchClicked(int state, int x, int y){
	//play button
	if (state != GLUT_UP) return guiType::MENU;
	if (buttons[1]->isSelected(x, height - y)) {
		return guiType::BUILD;
	}
	// help button
	else if((buttons[buttons.size() - 1]->isSelected(x, height - y))){
		return guiType::HELP;
	}
	// stay at the menu button
	else{
		return guiType::MENU;
	}
}

bool mainMenu::helpClicked(int state, int x, int y){
	//help button
	if (state != GLUT_UP) return false;
	return buttons[buttons.size() - 1]->isSelected(x, height - y);
}