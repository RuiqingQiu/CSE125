#pragma once
#include <vector>
#include <cmath>
#include "guiItem.h"
#include "button.h"

class scrollBox : public guiItem
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
	void translatePos(int x, int y) override;

	void init();
	void addListItem(char * filename );

	bool isClicked();
	void onClick();

	//regular items, just displays
	guiItem * scrollDisplay;
	button * upButton;
	button * downButton;

	//clickable items
	std::vector<button*> list;
};

