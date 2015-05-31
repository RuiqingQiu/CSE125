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
	if (name.length() >= MAX_NUMBER && enteringName){
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
		if (name.length() != 0 && enteringName == true){
			name.pop_back();
		}
		//delete ip address character
		else if (IPAdress.length() != 0 && enteringAddress == true){
			IPAdress.pop_back();
		}
		break;
	case 27:
		exit(0);
		break;
	case '1':
		if (enteringAddress)
			IPAdress.append("1");
		break;
	case '2':
		if (enteringAddress)
			IPAdress.append("2");
		break;
	case '3':
		if (enteringAddress)
			IPAdress.append("3");
		break;
	case '4':
		if (enteringAddress)
			IPAdress.append("4");
		break;
	case '5':
		if (enteringAddress)
			IPAdress.append("5");
		break;
	case '6':
		if (enteringAddress)
			IPAdress.append("6");
		break;
	case '7':
		if (enteringAddress)
			IPAdress.append("7");
		break;
	case '8':
		if (enteringAddress)
			IPAdress.append("8");
		break;
	case '9':
		if (enteringAddress)
			IPAdress.append("9");
		break;
	case '0':
		if (enteringAddress)
			IPAdress.append("0");
		break;
	case '.':
		if (enteringAddress)
			IPAdress.append(".");
		break;
	// need to read input for robot name, inheritanted from GameInputInterface
	case 'a':
		if (enteringName)
			name.append("a");
		break;
	case 'b':
		if (enteringName)
			name.append("b");
		break;
	case 'c':
		if (enteringName)
			name.append("c");
		break;
	case 'd':
		if (enteringName)
			name.append("d");
		break;
	case 'e':
		if (enteringName)
			name.append("e");
		break;
	case 'f':
		if (enteringName)
			name.append("f");
		break;
	case 'g':
		if (enteringName)
			name.append("g");
		break;
	case 'h':
		if (enteringName)
			name.append("h");
		break;
	case 'i':
		if (enteringName)
			name.append("i");
		break;
	case 'j':
		if (enteringName)
			name.append("j");
		break;
	case 'k':
		if (enteringName)
			name.append("k");
		break;
	case 'l':
		if (enteringName)
			name.append("l");
		break;
	case 'm':
		if (enteringName)
			name.append("m");
		break;
	case 'n':
		if (enteringName)
			name.append("n");
		break;
	case 'o':
		if (enteringName)
			name.append("o");
		break;
	case 'p':
		if (enteringName)
			name.append("p");
		break;
	case 'q':
		if (enteringName)
			name.append("q");
		break;
	case 'r':
		if (enteringName)
			name.append("r");
		break;
	case 's':
		if (enteringName)
			name.append("s");
		break;
	case 't':
		if (enteringName)
			name.append("t");
		break;
	case 'u':
		if (enteringName)
			name.append("u");
		break;
	case 'v':
		if (enteringName)
			name.append("v");
		break;
	case 'w':
		if (enteringName)
			name.append("w");
		break;
	case 'x':
		if (enteringName)
			name.append("x");
		break;
	case 'y':
		if (enteringName)
			name.append("y");
		break;
	case 'z':
		if (enteringName)
			name.append("z");
		break;
	case ' ':
		if (enteringName)
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

