
#include "stdafx.h"
#include "gui.h"
#include "GameCore.h"
#include "letters.h" // display textured letter

#define MAX_PLAYER 4

class mainMenu : public gui {

public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have
	void VOnClientUpdate(GameInfoPacket* info); //must have
	void drawAllItems(); // overwrite the gui drawAllItems function

	viewType mouseClickFunc(int state, int x, int y);

	std::vector<guiItem*> guiLetters; // keep track of the letter in the string, later combined with guiItems vector

private:
	//helper initialization functions
	void createButtons();
	void addLetters();

	// local variables to remembr the width and height
	int w; 
	int h;

	//pointers to special guiItems
	background * backimg;
	button * helpButton;
	button * playButton;
	button * exitButton;

	int playerReady;
	bool ready;
	int letterOffset; // tune the position of the letters
};