#include "stdafx.h"
#include "buildTimer.h"
#include "numbers.h"
#include <ctime>

// for display seconds, use buildTimer
#define MIN 10 // game lasts 10 minutes

// battle view timer extends buildTimer
class battleTimer : public buildTimer{

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

	//std::clock_t start;
	//int timeLeft;

	static string textPath;

};


