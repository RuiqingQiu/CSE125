#pragma once
#include "stdafx.h"
#include <ctime>
#include "numbers.h"

#define NUM_DIGITS 2
#define MAX_TIME 90

class buildTimer : public guiItem {
public:
	buildTimer();
	buildTimer(int x, int y);
	buildTimer(int x, int y, bool f);
	buildTimer(int x, int y, bool xf, bool yf);
	buildTimer(int x, int y, int w, int h);
	buildTimer(int x, int y, int w, int h, bool f);
	buildTimer(int x, int y, int w, int h, bool xf, bool yf);
	~buildTimer();

	void update();
	void draw();
	//void setScaling(bool xs, bool ys, int w, int h);
	void rePosition(int x, int y, int w, int h);

	std::clock_t start;
	int timeLeft;

	static string textPath;
protected:
	void createNumbers();
	numbers * digits[NUM_DIGITS];
};

