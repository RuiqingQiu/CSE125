#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){
	width = 0;
	height = 0;
	// right now whole main menu is clickable, single texture
	// need to add more buttons later
	buttons.push_back(new button("uiItem/images/background.jpg", 150, 330, 150, 100, true));
}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
	buttons.push_back(new button("uiItem/images/background.jpg", 150, 330, 150, 100, true));
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
		buttons[i]->onClick(x, height-y);
	}
}
