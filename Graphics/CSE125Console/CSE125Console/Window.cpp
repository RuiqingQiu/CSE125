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
#include "tiny_obj_loader.h"
#include "Model3D.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
//Init server info here later
void Window::initialize(void)
{
	GameView* view = new GameView();
	Cube* cube = new Cube(4);
	cube->localTransform.position = Vector3(0, 0, 0);
	cube->identifier = 1;
	//view->PushGeoNode(cube);
	g_pCore->pGameView = view;
	g_pCore->pGamePacketManager->ConnectToServer("127.1.1.1");
	//Setup the light
	Model3D *object = new Model3D("Pikachu.obj");
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.scale = Vector3(1, 1, 1);

	view->PushGeoNode(object);


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
	g_pCore->i_pInput->VProcessKeyInput(key, x, y);
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
	//glFrustum(-1, 1, -1 , 1, 1,5);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{

	//Manager get packet	
	GameInfoPacket* p = g_pCore->pGamePacketManager->tryGetGameInfo();
	if (p){
		switch (p->packet_types){
		case GAME_STATE:
			g_pCore->pGameView->VOnClientUpdate(p);
			break;
		case CONFIRM_CONNECTION:
			g_pCore->pPlayer->playerid = p->player_infos[0]->id;

		}
		//update
	}

	g_pCore->pGameView->VOnRender();
}
