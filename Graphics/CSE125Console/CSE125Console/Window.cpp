#include "stdafx.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "GameView.h"
#include "Cube.h"


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

static GameView* view;
static Cube* cube;

GamePacketManager* Window::manager;

//Init server info here later
void Window::initialize(void)
{
	manager = new GamePacketManager();

	view = new GameView();

	cube = new Cube(2);
	cube->localTransform.position = Vector3(0, 0, -5);
	cube->identifier = 1;
	view->PushGeoNode(cube);
	//Setup the light
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Call the display routine to draw the cube
    displayCallback();
}
void Window::processNormalKeys(unsigned char key, int x, int y){
	if (key == 27){
		exit(0);
	}
	else if (key == 'a'){
		
	}
	else if (key == 'w'){

	}
	else if (key == 's'){

	}
	else if (key == 'd'){

	}
}
//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0f, 0.0f, -5.0f);

	printf("display\n");

	//get net p, client loop  check packet, if so process then update object states, else render
	
	/*
	GameInfoPacket* g = new GameInfoPacket();
	PlayerInfo* p = new PlayerInfo();
	p->id = 1;
	p->x = 1;
	p->y = 0;
	p->z = -10;

	g->player_infos.push_back(p);
	*/


	//Manager get packet
	/*
	GameInfoPacket* p = manager->tryGetGameInfo();
	if (p){

		//update
		view->OnClientUpdate(p);
	}*/

	view->OnRender();
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}
