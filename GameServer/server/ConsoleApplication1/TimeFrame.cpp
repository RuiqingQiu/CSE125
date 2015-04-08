

/* TimeFrame.cpp */
#include "TimeFrame.h"

TimeFrame::TimeFrame()
{
	clockTime = clock();
	countdownTime = 0;
}

TimeFrame::~TimeFrame(){
	
}
// Start clock
void TimeFrame::startClock()
{
	clockTime = clock();
}

// Find the elapsed time since clock started
unsigned TimeFrame::getElapsedTime()
{
	return clock() - clockTime;
}

// Start countdown timer with a given time period (in seconds)
void TimeFrame::startCountdown(unsigned period)
{
	countdownPeriod = period * 1000;
	countdownTime = clock();
}

// Check if time period has elapsed since countdown timer started
int TimeFrame::checkCountdown()
{
	return (clock() - countdownTime) >= countdownPeriod;
}

// Sleep frame for a given time period (in milliseconds)
void TimeFrame::frameSleep(int milliseconds)
{
	Sleep(milliseconds);
}