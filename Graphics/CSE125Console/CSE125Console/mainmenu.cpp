#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){
	buttons.push_back(new button("uitexture.jpg", 100, 100, 100, 100));
}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
	buttons.push_back(new button("uitexture.jpg", 100, 100, 100, 100));
}

mainMenu::~mainMenu(){

}

void mainMenu::VOnRender(){
	set2d();
	/*
	buttons[0] = new button("C:/Users/miw034/Desktop/CSE125/Graphics/CSE125Console/CSE125Console/uitexture.jpg", width, height);
	
	this->drawButtons();
	*/

	drawButtons();

	set3d();
	
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info){

}

