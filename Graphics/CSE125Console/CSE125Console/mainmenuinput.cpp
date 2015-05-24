#include "stdafx.h"
#include "mainmenuinput.h"

mainMenuInput::mainMenuInput() :guiGameInput(){
	IPAdress = "128.54.70.34"; // test displaying the IP Address, need to change later
	g_pCore->pPlayer->name = name;
	g_pCore->pPlayer->IPAddress = IPAdress; // set the ip address in the game player object
}

mainMenuInput::~mainMenuInput(){
	name = "Anonymous";
}

// handle robot name input
void mainMenuInput::VProcessKeyInput(unsigned char key, int x, int y){
	
	// if the robot name is longer than max characters, doesn't allow user to add more letters
	if (name.length() >= MAX_NUMBER){
		// but allow the user to delete character
		if (key == 8){
			name.pop_back();
		}
		return;
	}
	//no key input yet except switching modes
	switch (key) {
	// "backspace is treated as ASCII 8 in opengl"
	case 8:
		// if string length is zero, cannot delete anymore
		if (name.length() != 0){
			name.pop_back();
		}
		break;
	case 27:
		exit(0);
		break;
	// need to read input for robot name, inheritanted from GameInputInterface
	case 'a':
		name.append("a");
		break;
	case 'b':
		name.append("b");
		break;
	case 'c':
		name.append("c");
		break;
	case 'd':
		name.append("d");
		break;
	case 'e':
		name.append("e");
		break;
	case 'f':
		name.append("f");
		break;
	case 'g':
		name.append("g");
		break;
	case 'h':
		name.append("h");
		break;
	case 'i':
		name.append("i");
		break;
	case 'j':
		name.append("j");
		break;
	case 'k':
		name.append("k");
		break;
	case 'l':
		name.append("l");
		break;
	case 'm':
		name.append("m");
		break;
	case 'n':
		name.append("n");
		break;
	case 'o':
		name.append("o");
		break;
	case 'p':
		name.append("p");
		break;
	case 'q':
		name.append("q");
		break;
	case 'r':
		name.append("r");
		break;
	case 's':
		name.append("s");
		break;
	case 't':
		name.append("t");
		break;
	case 'u':
		name.append("u");
		break;
	case 'v':
		name.append("v");
		break;
	case 'w':
		name.append("w");
		break;
	case 'x':
		name.append("x");
		break;
	case 'y':
		name.append("y");
		break;
	case 'z':
		name.append("z");
		break;
	case ' ':
		name.append(" ");
		break;
	default:
		break;
	}
	// set the gamecore player info at the mainmenuinput file
	g_pCore->pPlayer->name = name;
	g_pCore->pPlayer->IPAddress = IPAdress; // set the ip address in the game player object
	//cout << "robot name is " << g_pCore->pPlayer->name << endl;
}


void mainMenuInput::VProcessSpecialKey(int key, int x, int y){
	switch (key) {
		//move the new block to be added to the robot
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	default:
		break;
	}
}

