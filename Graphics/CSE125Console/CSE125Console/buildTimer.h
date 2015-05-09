#pragma once
#include "stdafx.h"
#include <ctime>
#include "numDisplay.h"

class buildTimer : public numDisplay {
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

	std::clock_t start;
	int timeLeft;

	static string textPath;
protected:
	virtual void init();
};

