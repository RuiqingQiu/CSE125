#pragma once

#include "gui.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);
	buildView(int w, int h, gui * hp, gui * s);

	void VOnRender();
	void createButtons();

	void onClick(int state, int x, int y);

	guiType switchClicked(int state, int x, int y);
	bool helpClicked(int state, int x, int y);

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
};

