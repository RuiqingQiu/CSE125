#pragma once
#include "guiItem.h"

class healthBar : public guiItem
{
public:
	healthBar();
	healthBar(int x, int y);
	healthBar(int x, int y, bool f);
	healthBar(int x, int y, bool xf, bool yf);
	healthBar(int x, int y, int w, int h);
	healthBar(int x, int y, int w, int h, bool f);
	healthBar(int x, int y, int w, int h, bool xf, bool yf);
	~healthBar();
};

