#include "stdafx.h"
#include "mainmenu.h"
#include <iostream>
#include <string>


mainMenu::mainMenu() : gui() {
	createButtons();
}

mainMenu::mainMenu(int w, int h) : gui(w, h) {
	createButtons();
}

mainMenu::~mainMenu(){

}

void mainMenu::createButtons() {

	button * robo = new button("menuItem/enterRobotName.jpg", width*0.3, height*0.5, 750, 100);
	robo->setScaling(true, true, width, height);
	
	button * play = new button("menuItem/play.jpg", width*0.43, height*0.3,260,50);
	play->setTexture("menuItem/play_sel.jpg", btnState::SELECTED);
	play->setTexture("menuItem/play_press.jpg", btnState::PRESSED);
	play->setScaling(true, true, width, height);

	button * help = new button("menuItem/help.jpg", width*0.43, height * 0.2,260,50);
	help->setTexture("menuItem/help_sel.jpg", btnState::SELECTED);
	help->setTexture("menuItem/help_press.jpg", btnState::PRESSED);
	help->setScaling(true, true, width, height);

	buttons.push_back(robo);
	buttons.push_back(play);
	buttons.push_back(help);

	backimg = new background("background1.jpg", width, height);
	guiItems.push_back(backimg);
}


void mainMenu::VOnRender(){
	GameView::VOnRender();
	set2d();
	drawAllItems();
	//using drawtext for now... ugly font though
	drawText(width * 0.6, height * 0.5, g_pCore->gui_Input->name, 1.0, 1.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24);

	set3d();
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
	
	if (state != GLUT_UP) return guiType::MENU;
	
	//play button
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