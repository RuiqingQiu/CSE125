
#include "stdafx.h"
#include "gui.h"
#include "background.h"
#include "GameCore.h"

class mainMenu : public gui {
public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have

	void VOnClientUpdate(GameInfoPacket* info); //must have

	void createButtons();

	viewType mouseClickFunc(int state, int x, int y);

	vector<button*> clickableItems;

	background * backimg;

};