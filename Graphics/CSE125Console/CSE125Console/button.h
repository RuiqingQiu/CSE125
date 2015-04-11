#pragma once

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

	bool isClicked(int x, int y);
	void onClick(int x int y);

private:

	char * name;

};

