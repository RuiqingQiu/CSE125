#include "stdafx.h"
#include "gui.h"


gui::gui() {
}

gui::gui(int w, int h) {
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
		if (!buttons[i]->isFixed())
			buttons[i]->translatePos(xdiff, ydiff);
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

	//draw stuff here

	/* note for gui people:
		make button class with atributes:
			texture
			on click
			size
			position
	*/
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

void gui::drawButtons() {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->draw();
	}
}