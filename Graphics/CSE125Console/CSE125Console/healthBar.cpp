#include "stdafx.h"
#include "healthBar.h"


healthBar::healthBar()
{
}

healthBar::healthBar(int x, int y) : guiItem("images/healthBar.jpg", x, y) {
}

healthBar::healthBar(int x, int y, bool f) : guiItem("images/healthBar.jpg", x, y, f) {
}

healthBar::healthBar(int x, int y, bool xf, bool yf) : guiItem("images/healthBar.jpg", x, y, xf, yf) {
}

healthBar::healthBar(int x, int y, int w, int h) : guiItem("images/healthBar.jpg", x, y, w, h) {
}

healthBar::healthBar(int x, int y, int w, int h, bool f) : guiItem("images/healthBar.jpg", x, y, w, h, f) {
}

healthBar::healthBar(int x, int y, int w, int h, bool xf, bool yf) : guiItem("images/healthBar.jpg", x, y, w, h, xf, yf) {
}

healthBar::~healthBar()
{
}
