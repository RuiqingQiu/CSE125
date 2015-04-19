#pragma once


#include "stdafx.h"
#include "gui.h"

class battleView : public gui {
public:
	battleView();
	battleView(int w, int h);

	void VOnRender();
	void createButtons();

	void onClick(int state, int x, int y);

	guiType switchClicked(int state, int x, int y);
	bool helpClicked(int state, int x, int y);

	~battleView();

	vector<button*> listItems;
};
