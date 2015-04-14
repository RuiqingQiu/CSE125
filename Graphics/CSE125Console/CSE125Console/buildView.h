#pragma once

#include "gui.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);
	buildView(int w, int h, gui * hp, gui * s);

	void VOnRender();
	void createButtons();

	void onClick(int x, int y);

	int switchClicked(int x, int y);
	bool helpClicked(int x, int y);

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
};

