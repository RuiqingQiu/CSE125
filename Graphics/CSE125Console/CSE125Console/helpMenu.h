#pragma once

#include "gui.h"
#include "background.h"

class helpMenu : public gui {

public:
	helpMenu();
	helpMenu(int w, int h);
	helpMenu(int w, int h, guiType r);
	~helpMenu();

	void createButtons();
	virtual void VOnRender();

	guiType switchClicked(int state, int x, int y);
	
	guiType returnTo;

	background * backimg;
};

