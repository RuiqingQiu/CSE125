#include "stdafx.h"
#include "gui.h"

/*
* things to implement:
* handling mouseclick events...
*		is this from g_pCore->i_pInput???
*		somehow need to connect buttons to core then....
*			i.e. g_pCore->pGamePacketManager->sendClick...??
*			need to ask graphics how this is done
*/

gui::gui() {
	buttons = std::vector<button*>();
	width = 0;
	height = 0;
}

gui::gui(int w, int h) {
	buttons = std::vector<button*>();
	width = w;
	height = h;
}

gui::~gui() {
}

void gui::VOnClientUpdate(GameInfoPacket* info) {
	//empty for now
}

void gui::setDimensions(int w, int h) {
	int xdiff = w - width;
	int ydiff = h - height;
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->rePosition(xdiff, ydiff, w, h);
	}
	for (int i = 0; i < guiItems.size(); i++) {
		guiItems[i]->rePosition(xdiff, ydiff, w, h);
	}
	width = w;
	height = h;
}

void gui::set2d() {
	//set up 2d
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void gui::set3d() {
	// Making sure we can render 3d again
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//SET back to white color for next render pass
	glColor3f(1, 1, 1);
}
//this is an example of how to draw 2d stuff in opengl that isn't affected by depth
// i am putting it all in gui class for 2d "setup"
//i want to move drawtext and other draw subroutines into a view class
// and have a battlefieldview, buildview, and menuview extend it
//we also need some sort of button class to store what texture goes with which button
void gui::VOnRender() {
	set2d();
	drawAllItems();
	set3d();
}

void gui::drawText(int x, int y, std::string text, float r, float g, float b, void * font) {
	glColor3f(r, g, b);//needs to be called before RasterPos
	glRasterPos2i(x, y);

	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		//this does nothing, color is fixed for Bitmaps when calling glRasterPos
		//glColor3f(1.0, 0.0, 1.0);
		glutBitmapCharacter(font, c);
	}
}

void gui::drawAllItems() {
	for (int i = 0; i < guiItems.size(); i++) {
		guiItems[i]->draw();
	}

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->draw();
	}
}

void gui::onClick(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height - y);
	}
}

guiType gui::switchClicked(int state, int x, int y) {
	std::cout << "need to implement!" << std::endl;
	return guiType::CONSOLE;
}

bool gui::helpClicked(int state, int x, int y) {
	std::cout << "need to implement!" << std::endl;
	return false;
}

void gui::passiveMouseFunc(int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->onHover(x, height - y);
	}
}
