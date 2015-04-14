#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){
	width = 0;
	height = 0;

	createButtons();
}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
	
	createButtons();
}

mainMenu::~mainMenu(){

}

void mainMenu::createButtons() {
	button * help = new button("uiItem/buttons/menuItem/help.jpg", width*0.5, height * 0.3, 100, 30);
	help->setScaling(true, true, width, height);

	button * play = new button("uiItem/buttons/menuItem/play.jpg", width*0.5, height*0.4, 100, 30);
	play->setScaling(true, true, width, height);

	button * robo = new button("uiItem/buttons/menuItem/enterRobotName.jpg", width*0.4, height*0.5, 300, 70);
	robo->setScaling(true, true, width, height);

	buttons.push_back(robo);
	buttons.push_back(play);
	buttons.push_back(help);
}


void mainMenu::VOnRender(){
	set2d();
	drawAllItems(); 
	set3d();
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info){

}

void mainMenu::onClick(int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(x, height - y);
	}
}

int mainMenu::switchClicked(int x, int y){
	//play button
	std::cout << "Height: " << height << std::endl;
	if (buttons[1]->isClicked(x, height - y)) {
		return BUILD;
	}
	// help button
	else if((buttons[buttons.size() - 1]->isClicked(x, height - y))){
		return HELP;
	}
	// stay at the menu button
	else{
		return MENU;
	}
}

bool mainMenu::helpClicked(int x, int y){
	//help button
	return buttons[buttons.size() - 1]->isClicked(x, height - y);
}