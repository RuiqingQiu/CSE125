#pragma once
#include "stdafx.h"
#include "gui.h"
#include "battletimer.h"
#include "healthBar.h"
#include "cooldownDisplay.h"

class battleView : public gui {
public:
	battleView();
	battleView(int w, int h);
	~battleView();

	void VOnRender();
	void VUpdate();
	void createButtons();

	viewType mouseClickFunc(int state, int x, int y);
	
	vector<button*> listItems;
	battleTimer * timer;
	bool updateview;

	healthBar * healthDisplay;

	cooldownDisplay * cooldown;
};
