#include "stdafx.h"
#include "buildGameView.h"


buildGameView::buildGameView()
{
}


buildGameView::~buildGameView()
{
}

void buildGameView::VUpdate() {

}

void buildGameView::VOnRender() {
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	pViewCamera->setUpCamera();

	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());

	robo->draw();


}