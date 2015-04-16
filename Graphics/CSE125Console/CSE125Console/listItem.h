#pragma once
#include <vector>
#include "button.h"
class listItem : public button
{
public:
	listItem();
	listItem(string filename);
	listItem(string filename, int x, int y);
	listItem(string filename, int x, int y, bool f);
	listItem(string filename, int x, int y, bool xf, bool yf);
	listItem(string filename, int x, int y, int w, int h);
	listItem(string filename, int x, int y, int w, int h, bool f);
	listItem(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~listItem();

	virtual void init() override;

	virtual void draw();
	virtual void rePosition(int x, int y, int w, int h);

	virtual void onClick(int state, int x, int y);

	bool showPrev;
	bool showSubList;

	std::vector<listItem *> subList;
};

