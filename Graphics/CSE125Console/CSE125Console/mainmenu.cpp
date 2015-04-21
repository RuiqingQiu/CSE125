#include "stdafx.h"
#include "mainmenu.h"
#include <iostream>
#include <string>

int span = 0.2; // remember end of the string that has already been added to the guiItem array
int start_w; // start to display robot name
int start_h;
mainMenu::mainMenu() : gui() {
	w = width;
	h = height;
	start_w = w * 0.5;
	start_h = h * 0.55;
	createButtons();
}

mainMenu::mainMenu(int w, int h) : gui(w, h) {
	w = width;
	h = height;
	start_w = w * 0.5;
	start_h = h * 0.55;
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
	//guiItems.push_back(backimg);
	guiTexts.push_back(backimg); // push in to the guiTexts vector
}

// add letters to the guiItem array
void mainMenu::addLetters(){
	w = width;
	h = height;
	start_w = width * 0.5;
	start_h = height * 0.55;

	string n = g_pCore->i_pInput->name; // get the name of game core
	guiLetters.clear(); // clear the guiLetters every time and start over
	int counter = 0;
	// loop through the string
	for (string::iterator it = n.begin(); it != n.end(); ++it) {
		letters *l = new letters(start_w + counter * span, start_h + counter * span); // pass in x,y position
		counter++;
		l->letterToShow = int(*it) - 97; // from char to array index
		guiLetters.push_back(l);
	}

	guiItems.clear(); // clear the guiItem to avoid adding elements all more than once
	// combine guiTexts and guiLetters
	for (std::vector<guiItem*>::iterator it = guiTexts.begin(); it != guiTexts.end(); ++it) {
		guiItems.push_back(*it); // add guiTexts first 
	}
	// add guiletters afterwards
	for (std::vector<guiItem*>::iterator it = guiLetters.begin(); it != guiLetters.end(); ++it){
		guiItems.push_back(*it);
	}
}

void mainMenu::VOnRender(){
	GameView::VOnRender();
	set2d();
	addLetters();
	drawAllItems();
	drawText(width * 0.5, height * 0.55, g_pCore->i_pInput->name, 1.0, 1.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24);
	set3d();
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info){

}


viewType mainMenu::mouseClickFunc(int state, int x, int y){
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height - y);
	}

	if (state != GLUT_UP) return viewType::MENU;
	
	//play button
	if (buttons[1]->isSelected(x, height - y)) {
		return viewType::BUILD;
	}
	// help button
	else if((buttons[buttons.size() - 1]->isSelected(x, height - y))){
		return viewType::HELP;
	}
	// stay at the menu button
	return viewType::MENU;
}