#pragma once
#include "guiItem.h"

class background : public guiItem
{
public:
	background();
	background(string filename);
	background(string filename, int w, int h);
	~background();

	virtual void init();
	virtual void rePosition(int x, int y, int w, int h);
};

