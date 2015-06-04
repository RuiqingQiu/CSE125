#pragma once
#include "stdafx.h"
#include "gui.h"
#include "sound.h"

enum helpPage {
    MAIN_PAGE = 0,
    BUILD_PAGE = 1,
    BATTLE_PAGE = 2,
};
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
    
    vector<background * > pages;
    
    button * backButton;
    button * next;
    button * prev;
    
    helpPage currentPage;
	int prevMouseState;
private:
	Sound* sound;
};

