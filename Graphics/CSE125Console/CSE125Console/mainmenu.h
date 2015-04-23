
#include "stdafx.h"
#include "gui.h"
#include "GameCore.h"
#include "letters.h" // display textured letter

class mainMenu : public gui {

public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have

	void VOnClientUpdate(GameInfoPacket* info); //must have

	void createButtons();

	void addLetters(); // helper function
	void drawAllItems(); // overwrite the gui drawAllItems function

	viewType mouseClickFunc(int state, int x, int y);

	vector<button*> clickableItems;
	std::vector<guiItem*> guiLetters; // keep track of the letter in the string, later combined with guiItems vector
	

	background * backimg;

	int w; // local variables to remembr the width and height
	int h; 

};