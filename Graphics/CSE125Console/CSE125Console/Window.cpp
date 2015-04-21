#include "stdafx.h"
#include <iostream>

#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "viewFactory.h"
#include "Cube.h"
#include "tiny_obj_loader.h"
#include "Model3D.h"
#include "SkyBox.h"
#include "Plane.h"
#include "HardShadowView.h"
#include "TestView.h"
#include "Teapot.h"
#define TESTCAM 1


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

static viewFactory * factory; // factory of gui

static int counter = 0;
static Cube* cube;
static Model3D*object;
//Init server info here later

void Window::initialize(void)
{
	//factory = new viewFactory(width, height);
	factory = new viewFactory(true);  //for no gui
	g_pCore->skybox = new SkyBox();
	g_pCore->pPlayer->playerid = 1;
	GameView* view = new GameView();

	//Teapot* t = new Teapot(2);

	//set color
	//glColor3f(1, 1, 1);
	cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, -5);
	//cube->localTransform.scale= Vector3(1, 0.00001, 1);
	cube->identifier = 1;
	view->PushGeoNode(cube);

	view->PushGeoNode(g_pCore->skybox);

	//setup light
	view->PushGeoNode(g_pCore->light);
	//g_pCore->battlemode->PushGeoNode(g_pCore->light);

	Plane* p = new Plane(50);
	p->setColor(1, 1, 0);
	p->localTransform.position = Vector3(0, -5, 0);
	p->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(p);
	/*
	p = new Plane(50);
	p->setColor(1, 0, 0);
	p->localTransform.position = Vector3(20, 0, 0);
	p->localTransform.rotation = Vector3(0, 0, 90);
	view->PushGeoNode(p);

	p = new Plane(50);
	p->setColor(0, 1, 0);
	p->localTransform.position = Vector3(-20, 0, 0);
	p->localTransform.rotation = Vector3(0, 0, -90);
	view->PushGeoNode(p);*/
	/*
	Model3D *object = new Model3D("woodcube.obj");
	object->localTransform.position = Vector3(0, 0, -10);
	object->localTransform.scale = Vector3(1, 1, 1);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(object);
	*/
	factory->battlemode->PushGeoNode(object);
	factory->battlemode->PushGeoNode(g_pCore->skybox);
	factory->battlemode->PushGeoNode(g_pCore->light);
	factory->battlemode->PushGeoNode(p);

	//test shadow view
	//HardShadowView* shadowview = new HardShadowView();
	//factory->defaultView = shadowview;

	//setup camera
	*g_pCore->pGameView->pViewCamera->position = Vector3(0, 0, 10);

	//setup shader
	//init shader
	//GLuint program = LoadShader("shadow.vert", "shadow.frag");
	//glUseProgram(program);

	//setup factory
	factory->defaultView = view;
	factory->setView();
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;

	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.32");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.91.53");
	if (TESTCAM)
	{
		g_pCore->pGameView->pViewCamera->FollowingTarget = cube;
	}
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback() 
{
	g_pCore->pGameView->VUpdate();
	factory->idleFunc();
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;

    //Call the display routine to draw the cube
    displayCallback();
}

void Window::processNormalKeys(unsigned char key, int x, int y) 
{
	g_pCore->i_pInput->VProcessKeyInput(key, x, y);
	factory->switchView(key);
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;
	
	if (TESTCAM){
		if (key == ','){
			cube->localTransform.rotation.y += 1;
		}
		else if (key == '.'){
			cube->localTransform.rotation.y -= 1;
		}
	}
	
}

void Window::processSpecialKeys(int key, int x, int y) {
	g_pCore->i_pInput->VProcessSpecialKey(key, x, y);
}

void Window::processMouseClick(int button, int state, int x, int y) {
	g_pCore->i_pInput->VProcessMouseClick(button, state, x, y);
	factory->mouseFunc(button, state, x, y);
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;
}

void Window::processPassiveMouse(int x, int y) {
	g_pCore->i_pInput->VProcessPassiveMouse(x, y);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h) {
    Window::width = w;                                                       //Set the window width
	Window::height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(60.0, double(Window::width) / (double)Window::height, 1, 1000.0); //Set perspective projection viewing frustum
	//glFrustum(-1, 1, -1 , 1, 1,5);

	factory->reshapeFunc(w, h);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.

void Window::displayCallback() {
	counter = (counter + 1) % 360;
	
	//object->localTransform.rotation.y = counter;
	//Manager get packet	
	GameInfoPacket* p = g_pCore->pGamePacketManager->tryGetGameInfo();
	if (p!=nullptr) {
		switch (p->packet_types){
			case GAME_STATE:{
				g_pCore->pGameView->VOnClientUpdate(p);
				break;
			}
			case CONFIRM_CONNECTION:{
				g_pCore->pPlayer->playerid = p->player_infos[0]->id;
				break;
			}
			default:{
				break;
			}
		}
		//update
	}
	
	g_pCore->pGameView->VOnRender();

	//cout << "on display " << endl;

	//test for camera
	
	//glPopMatrix();
	//Tell OpenGL to clear any outstanding commands in its command buffer
	//This will make sure that all of our commands are fully executed before
	//we swap buffers and show the user the freshly drawn frame
	glFlush();
	//Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
	glutSwapBuffers();

}
