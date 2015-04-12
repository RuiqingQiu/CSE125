#pragma once

#include "gui.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);

	void VOnRender();
	void createButtons();

	void onClick(int x, int y);

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
};

