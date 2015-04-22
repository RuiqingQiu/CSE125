#include "stdafx.h"
#include "battletimer.h"

battleTimer::battleTimer() : buildTimer() {
	createNumbers();
}

battleTimer::battleTimer(int x, int y) :
buildTimer(x, y) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool f) :
buildTimer(x, y, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool xf, bool yf) :
buildTimer(x, y, xf, yf) {
	createNumbers();
}
battleTimer::battleTimer(int x, int y, int w, int h) :
buildTimer(x, y, w, h) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool f) :
buildTimer(x, y, w, h, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool xf, bool yf) :
buildTimer(x, y, w, h, xf, yf) {
	createNumbers();
}

battleTimer::~battleTimer() {
}

void battleTimer::update(){


}


void battleTimer::draw(){

}


void battleTimer::rePosition(int x, int y, int w, int h){


}

