#pragma once

#include <vector>
#include "numbers.h"


class numDisplay : public guiItem
{
public:
	numDisplay();
	numDisplay(string filename);
	numDisplay(string filename, int x, int y);
	numDisplay(string filename, int x, int y, bool f);
	numDisplay(string filename, int x, int y, bool xf, bool yf);
	numDisplay(string filename, int x, int y, int w, int h);
	numDisplay(string filename, int x, int y, int w, int h, bool f);
	numDisplay(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~numDisplay();

protected:
	void createNumbers();
	vector<numbers *> digits;
};

