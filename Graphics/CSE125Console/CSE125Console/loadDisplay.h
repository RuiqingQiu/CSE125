#pragma once
#include "guiItem.h"

class loadDisplay : public guiItem
{
public:
	loadDisplay();
	loadDisplay(int x, int y);
	loadDisplay(int x, int y, bool f);
	loadDisplay(int x, int y, bool xf, bool yf);
	loadDisplay(int x, int y, int w, int h);
	loadDisplay(int x, int y, int w, int h, bool f);
	loadDisplay(int x, int y, int w, int h, bool xf, bool yf);
	~loadDisplay();

	void createText();
	virtual void update();
	virtual void draw();
	virtual void rePosition(int x, int y, int w, int h);

	static string textPath;

	guiItem * loadingText;

};

