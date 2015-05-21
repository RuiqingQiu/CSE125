#pragma once
#include "stdafx.h"
#include "gui.h"
#include "healthBar.h"
#include "cooldownDisplay.h"

class battleView : public gui {
public:
	battleView();
	battleView(int w, int h);
	~battleView();

	void VOnRender();
	void VUpdate();
	void setDimensions(int w, int h);
	void createButtons();

	viewType mouseClickFunc(int state, int x, int y);
	
	vector<button*> listItems;
	battleTimer * timer;
	bool updateview;

	void updateHealth(float current, float max);
	void updateName(string name);

	cooldownDisplay * cooldown;
	background * takeDamage;
	bool damageTaken;

private:
	healthBar * healthDisplay;

	float currDuration = 0;
	float maxDuration = 3;
};
