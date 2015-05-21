#include "stdafx.h"
#include "numDisplay.h"

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

	void updateTime(int time);

	//no longer use local clock, use server sent time
	//std::clock_t start;
private:
	int minLeft;
	int secLeft;

	static string textPath;

	guiItem * colon;
};


