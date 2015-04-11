#include "stdafx.h"
#include "mainmenu.h"


mainMenu::mainMenu(){

}

mainMenu::mainMenu(int w, int h){
	width = w;
	height = h;
}

mainMenu::~mainMenu(){

}

void mainMenu::VOnRender(){
	texture[0] = SOIL_load_OGL_texture
		(

		"uitexture.jpg"
		//"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airFT.tga"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_north.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[0] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return;
	}
	else{
		printf("SOIL loading success\n");
	}
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info){

}

