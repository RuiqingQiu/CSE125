#include "stdafx.h"
#include "guiItem.h"
#include "numbers.h"
#include <ctime>

// for display seconds, use buildTimer
#define MIN 10 // game lasts 10 minutes
#define MAX_TIME 60
#define NUM_DIGITS 4
#define DIGITS 2

// battle view timer extends buildTimer
class battleTimer : public guiItem{

public:
	battleTimer();
	battleTimer(int x, int y);
	battleTimer(int x, int y, bool f);
	battleTimer(int x, int y, bool xf, bool yf);
	battleTimer(int x, int y, int w, int h);
	battleTimer(int x, int y, int w, int h, bool f);
	battleTimer(int x, int y, int w, int h, bool xf, bool yf);
	~battleTimer();

	void update();
	void draw();
	void rePosition(int x, int y, int w, int h);
	void createNumbers();

	std::clock_t start;
	int minLeft;
	int secLeft;

	static string textPath;
	numbers * digits[NUM_DIGITS];
};


