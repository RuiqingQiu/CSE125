#pragma once
#include <vector>
#include <cmath>
#include "guiItem.h"
#include "button.h"
#include "listItem.h"

#define MAXDISPLAY 10

class scrollBox : public button
{
private:
	//scrollbox.jpg size is 1000x1000 px
	int default_w = 1000;
	int default_h = 1200;

public:
	scrollBox();
	scrollBox(int x, int y);
	scrollBox(int x, int y, bool f);
	scrollBox(int x, int y, bool xf, bool yf);
	scrollBox(int x, int y, double s);
	scrollBox(int x, int y, double s, bool f);
	scrollBox(int x, int y, double s, bool xf, bool yf);
	~scrollBox();

	void draw() override;
	void rePosition(int x, int y, int w, int h) override;

	void init();
	void addListItem(string filename, string fileType, bool hasSel, bool hasPress);
	void addsubListItem(string filename, string fileType, int id, bool hasSel, bool hasPress);

	bool isSelected(int x, int y);
	void onClick(int state, int x, int y);
	void onHover(int x, int y);

	//clickable items
	std::vector<listItem*> list;

	button * addButton;
	button * removeButton;
	button * clearButton;
	int currentSelection = -1;

private:
	double scale;
	int getTotalSize();

	//regular items, just displays
	guiItem * scrollDisplay;
	//button * upButton;
	//button * downButton;

	int displayIdx;
};

