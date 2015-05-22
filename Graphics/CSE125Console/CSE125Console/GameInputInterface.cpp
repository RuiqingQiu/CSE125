#include "stdafx.h"
#include "GameInputInterface.h"


GameInputInterface::GameInputInterface()
{
	// initialize the string
	name = "";
	IPAdress = "";
}


GameInputInterface::~GameInputInterface()
{
}


void GameInputInterface::VProcessKeyInput(unsigned char key, int x, int y)
{
	//This method should always be overrided!
	//implement here just to avoid compiler error
	printf("This need to be implemented please FIX\n");
}

void GameInputInterface::VProcessSpecialKey(int key, int x, int y){
	//This method should always be overrided!
	//implement here just to avoid compiler error
	printf("This need to be implemented please FIX\n");
}

void GameInputInterface::VProcessMouseClick(int button, int state, int x, int y) {
	//This method should always be overrided!
	//implement here just to avoid compiler error
	printf("This need to be implemented please FIX\n");
}
void GameInputInterface::VProcessPassiveMouse(int x, int y) {
	//This method should always be overrided!
	//implement here just to avoid compiler error
	printf("This need to be implemented please FIX\n");
}

void GameInputInterface::VProcessMotion(int x, int y) {
	//This method should always be overrided!
	//implement here just to avoid compiler error
	printf("This need to be implemented please FIX\n");
}
void GameInputInterface::VProcessKeyInputUp(unsigned char key, int x, int y){

}
