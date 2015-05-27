#pragma once
#include "stdafx.h"
#include "gui.h"
#include "numDisplay.h"

class endView : public gui {
public:
	endView();
	endView(int w, int h);
	~endView();

	void VUpdate();

	void createDisplay();

	background * img;

	numDisplay * player;
	numDisplay * deaths;
	numDisplay * takedowns;
	numDisplay * rank;
	
	float numDeaths;
	float numTakedowns;
	float myRank;
};

