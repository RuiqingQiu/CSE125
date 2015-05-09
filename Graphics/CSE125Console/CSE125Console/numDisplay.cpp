#include "stdafx.h"
#include "numDisplay.h"


numDisplay::numDisplay() : guiItem() {
	createNumbers();
}

numDisplay::numDisplay(string filename) : guiItem(filename) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y) : guiItem(filename, x, y) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool f) : guiItem(filename, x, y, f) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool xf, bool yf) : guiItem(filename, x, y, xf, yf) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h) : guiItem(filename, x, y, w, h) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool f) : guiItem(filename, x, y, w, h, f) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool xf, bool yf) : guiItem(filename, x, y, w, h, xf, yf) {
	createNumbers();
}

numDisplay::~numDisplay() {
	for (int i = 0; i < digits.size(); i++) {
		delete digits[i];
	}
	digits.clear();
}

void numDisplay::createNumbers() {

}