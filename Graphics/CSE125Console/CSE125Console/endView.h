#pragma once
#include "stdafx.h"
#include "gui.h"
#include "numDisplay.h"

class letters;

class endView : public gui {
public:
	endView();
	endView(int w, int h);
	~endView();

	void VUpdate();
	void VOnRender();

	void createDisplay();

	background * img;

	numDisplay * player;
	numDisplay * deaths;
	numDisplay * takedowns;
	numDisplay * rank;
	
	float numDeaths;
	float numTakedowns;
	float myRank;

	void updateRobotName(string name);

private:
	vector<letters> roboName;
};

