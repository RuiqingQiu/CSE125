#pragma once

#include "gui.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);

	void VOnRender();
	void createButtons();

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
};

