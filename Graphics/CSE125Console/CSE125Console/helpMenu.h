#pragma once
#include "stdafx.h"
#include "gui.h"

class helpMenu : public gui {

public:
	helpMenu();
	helpMenu(int w, int h);
	helpMenu(int w, int h, viewType r);
	~helpMenu();

	void createButtons();
	virtual void VOnRender();

	viewType mouseClickFunc(int state, int x, int y);
	
	viewType returnTo;
	background * backimg;
};
