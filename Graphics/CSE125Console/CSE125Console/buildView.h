#pragma once

#include "gui.h"

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);

	void VOnRender();
	void createButtons();

	void onClick(int state, int x, int y);

	guiType switchClicked(int state, int x, int y);
	bool helpClicked(int state, int x, int y);

	//gameplay logic
	bool addBlock(int state, int x, int y);
	bool removeBlock(int state, int x , int y);

	~buildView();

	vector<button*> listItems;
	scrollBox * scroll;
};

