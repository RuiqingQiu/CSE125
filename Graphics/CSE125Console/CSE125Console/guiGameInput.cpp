#include "stdafx.h"
#include "guiGameInput.h"


guiGameInput::guiGameInput()
{
}


guiGameInput::~guiGameInput()
{
}

void guiGameInput::VProcessKeyInput(unsigned char key, int x, int y) {
	//no key input yet except switching modes
	switch (key) {
	    // "backspace is treated as ASCII 8 in opengl"
		case 8:
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
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'b':
			name.append("b");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'c':
			name.append("c");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'd':
			name.append("d");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'e':
			name.append("e");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'f':
			name.append("f");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'g':
			name.append("g");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'h':
			name.append("h");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'i':
			name.append("i");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'j':
			name.append("j");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'k':
			name.append("k");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'l':
			name.append("l");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'm':
			name.append("m");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'n':
			name.append("n");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'o':
			name.append("o");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'p':
			name.append("p");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'q':
			name.append("q");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'r':
			name.append("r");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 's':
			name.append("s");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 't':
			name.append("t");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'u':
			name.append("u");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'v':
			name.append("v");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'w':
			name.append("w");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'x':
			name.append("x");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'y':
			name.append("y");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;
		case 'z':
			name.append("z");
			cout << "Enter !!!! in guiGameInput.cpp" << endl;
			break;

		default:
			break;
	}
}

void guiGameInput::VProcessSpecialKey(int key, int x, int y) {
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

void guiGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//check which button was pressed here
	viewType s = g_pCore->pGameView->mouseClickFunc(state, x, y);
}

void guiGameInput::VProcessPassiveMouse(int x, int y) {
	g_pCore->pGameView->passiveMouseFunc(x, y);
}