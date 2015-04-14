#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){
	width = 0;
	height = 0;
	// right now whole main menu is clickable, single texture
	// need to add more buttons later
	buttons.push_back(new button("uiItem/buttons/menuItem/enterRobotName.jpg", 120, 170, 300, 70, true));
	//play.jpg is 47 2 * 139
	buttons.push_back(new button("uiItem/buttons/menuItem/play.jpg", 190, 100, 150, 50, true));
	//help.jpg : 300*107
	buttons.push_back(new button("uiItem/buttons/menuItem/help.jpg", 190, 45, 150, 50, true));
}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
	buttons.push_back(new button("uiItem/buttons/menuItem/enterRobotName.jpg", 120, 170, 300, 70, true));
	//play.jpg is 47 2 * 139
	buttons.push_back(new button("uiItem/buttons/menuItem/play.jpg", 190, 100, 150, 50, true));
	//help.jpg : 300*107
	buttons.push_back(new button("uiItem/buttons/menuItem/help.jpg", 190, 45, 150, 50, true));
}

mainMenu::mainMenu(int w, int h, gui * hp, gui * s){
	width = w;
	height = h;
	buttons.push_back(new button("uiItem/buttons/menuItem/2.jpg", 150, 330, 150, 100, true));
}

mainMenu::~mainMenu(){

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