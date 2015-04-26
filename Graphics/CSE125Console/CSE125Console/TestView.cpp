#include "stdafx.h"
#include "TestView.h"

TestView::TestView(){

}

TestView::~TestView(){

}

void TestView::VOnRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
	glutSolidTeapot(1);
	glutSwapBuffers();
}
void TestView::VOnClientUpdate(GameInfoPacket* info){

}
