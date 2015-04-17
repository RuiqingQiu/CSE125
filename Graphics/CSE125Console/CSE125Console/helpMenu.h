#pragma once

#include "gui.h"

class helpMenu : public gui {

public:
	helpMenu();
	helpMenu(int w, int h);
	helpMenu(int w, int h, guiType r);
	~helpMenu();

	void createButtons();

	guiType switchClicked(int state, int x, int y);
	
};

