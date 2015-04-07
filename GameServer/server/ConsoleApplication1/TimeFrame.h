/* TimeFrame.h */
#ifndef _TIME_FRAME_H_
#define _TIME_FRAME_H_

#include <windows.h>
#include <ctime>

class TimeFrame {
private:
	unsigned clockTime;
	unsigned countdownPeriod;
	unsigned countdownTime;

public:
	TimeFrame();
	~TimeFrame();

	// Start clock
	void startClock();

	// Find the elapsed time since clock started
	unsigned getElapsedTime();

	// Start countdown timer with a given time period (in seconds)
	void startCountdown(unsigned);

	// Check if time period has elapsed
	int checkCountdown();

	// Sleep frame for a given time period (in milliseconds)
	void frameSleep(int milliseconds);
};

#endif