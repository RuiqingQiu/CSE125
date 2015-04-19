#pragma once
#include <ctime>
#include "numbers.h"

#define NUM_DIGITS 2
#define MAX_TIME 20

class buildTimer : public guiItem {
public:
	buildTimer();
	buildTimer(string filename);
	buildTimer(string filename, int x, int y);
	buildTimer(string filename, int x, int y, bool f);
	buildTimer(string filename, int x, int y, bool xf, bool yf);
	buildTimer(string filename, int x, int y, int w, int h);
	buildTimer(string filename, int x, int y, int w, int h, bool f);
	buildTimer(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~buildTimer();

	void update();
	void draw();
	//void setScaling(bool xs, bool ys, int w, int h);
	void rePosition(int x, int y, int w, int h);

	std::clock_t start;
	int timeLeft;
private:
	void createNumbers();

	numbers * digits[NUM_DIGITS];
};

