#pragma once

#include <vector>
#include "numbers.h"

enum displayConstants {
	DEFAULT_NUM_DIGITS = 2,
	DEFAULT_NUM_DIGITS_FOR_MAINMENU = 1,
	BUILD_MAX_TIME = 90,
	MIN = 5,
	BATTLE_MAX_TIME = 60,
	BATTLE_NUM_DIGITS = 4,
};

class numDisplay : public guiItem
{
public:
	numDisplay();
	numDisplay(string filename);
	numDisplay(string filename, int x, int y);
	numDisplay(string filename, int x, int y, bool f);
	numDisplay(string filename, int x, int y, bool xf, bool yf);
	numDisplay(string filename, int x, int y, int w, int h);
	numDisplay(string filename, int x, int y, int w, int h,int mainmenuLoading); // loading view constructor
	numDisplay(string filename, int x, int y, int w, int h, bool f);
	numDisplay(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~numDisplay();

	virtual void update();
	virtual void draw();
	virtual void rePosition(int x, int y, int w, int h);

	float displayValue;
	int mainmenuLoading; // mainmenu and build view has different number position

protected:

	virtual void createNumbers();

	vector<numbers *> digits;
	int num_digits;

	//for setting size and position
	double off;
	int nSize;
};

