#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){
	width = 0;
	height = 0;
	//right now whole main menu is clickable, single texture
	//buttons.push_back(new button("uiItem/images/menuItem/background.jpg", 0, 0, width, height));


	buttons.push_back(new button("uiItem/images/background.jpg", 150, 330, 150, 100, true));
	//buttons.push_back(new button("uiItem/buttons/listItem/armor.jpg", 0, 0, width, height, true));
}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
	buttons.push_back(new button("uiItem/images/background.jpg", 150, 330, 150, 100, true));
	//buttons.push_back(new button("uiItem/buttons/listItem/armor.jpg", 0, 0, width, height, true));

	//buttons.push_back(new button("uitexture.jpg", 0, 0, width, height));
	//buttons.push_back(new button("C:/Users/miw034/Desktop/CSE125/Graphics/CSE125Console/CSE125Console/uitexture.jpg", 20, 20, 100, 30, true));
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