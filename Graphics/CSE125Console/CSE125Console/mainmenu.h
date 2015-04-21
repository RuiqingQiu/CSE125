
#include "stdafx.h"
#include "gui.h"
#include "background.h"
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

	void addLetters();

	viewType mouseClickFunc(int state, int x, int y);

	vector<button*> clickableItems;
	std::vector<guiItem*> guiLetters; // keep track of the letter in the string, later combined with guiItems vector
	std::vector<guiItem*> guiTexts; // keep track of all the text displayed on the main menu

	background * backimg;
	int w; // local variables to remembr the width and height
	int h; 

};