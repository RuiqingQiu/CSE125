#pragma once

#include "gui.h"
#include "buildTimer.h"
#include "scoreBox.h"
#include "Cube.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);

	void VOnRender();
	void VUpdate();
	void createButtons();

	viewType mouseClickFunc(int state, int x, int y);

	viewType checkTimeOut();

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
	buildTimer * timer;
	scoreBox * score;
	bool updateview;
};

