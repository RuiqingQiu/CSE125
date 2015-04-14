#pragma once
#include "stdafx.h"

#include "guiItem.h"

class button : public guiItem
{
public:
	button();
	button(char * filename);
	button(char * filename, int x, int y);
	button(char * filename, int x, int y, bool f);
	button(char * filename, int x, int y, bool xf, bool yf);
	button(char * filename, int x, int y, int w, int h);
	button(char * filename, int x, int y, int w, int h, bool f);
	button(char * filename, int x, int y, int w, int h, bool xf, bool yf);
	~button();

	virtual bool isClicked(int x, int y);
	virtual void onClick(int x, int y);

//private:
	//debugging
	char * name;

};

