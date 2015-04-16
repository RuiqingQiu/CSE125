#pragma once
#include "stdafx.h"

#include "guiItem.h"

class button : public guiItem
{
public:
	button();
	button(string filename);
	button(string filename, int x, int y);
	button(string filename, int x, int y, bool f);
	button(string filename, int x, int y, bool xf, bool yf);
	button(string filename, int x, int y, int w, int h);
	button(string filename, int x, int y, int w, int h, bool f);
	button(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~button();

	virtual void init() override;

	virtual bool isClicked(int x, int y);
	virtual void onClick(int state, int x, int y);

//private:
	//debugging
	string name;

};

