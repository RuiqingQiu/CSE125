#include "stdafx.h"
#include <ctime>
#include "buildTimer.h"

class battleTimer : public numDisplay {

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

	guiItem * colon;
};


