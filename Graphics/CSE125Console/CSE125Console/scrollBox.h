#pragma once
#include <vector>
#include <cmath>
#include "guiItem.h"
#include "button.h"

class scrollBox : public button
{
private:
	char * BOXLOC = "uiItem/scrollbox/scrollbox.jpg";
	std::string LISTLOC = "uiItem/buttons/listItem/";

public:
	scrollBox();
	scrollBox(int x, int y);
	scrollBox(int x, int y, bool f);
	scrollBox(int x, int y, bool xf, bool yf);
	scrollBox(int x, int y, int w, int h);
	scrollBox(int x, int y, int w, int h, bool f);
	scrollBox(int x, int y, int w, int h, bool xf, bool yf);
	~scrollBox();

	void draw() override;
	void rePosition(int x, int y, int w, int h) override;

	void init();
	void addListItem(char * filename );

	bool isClicked(int x, int y);
	void onClick(int x, int y);

private:
	//regular items, just displays
	guiItem * scrollDisplay;
	button * upButton;
	button * downButton;

	//clickable items
	std::vector<button*> list;
	int displayIdx;
};

