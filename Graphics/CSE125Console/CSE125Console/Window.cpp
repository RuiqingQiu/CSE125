#include "stdafx.h"
#include <iostream>

#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "GameView.h"
#include "Cube.h"
#include "tiny_obj_loader.h"
#include "Model3D.h"
#include "SkyBox.h"
#include "Plane.h"
#include "HardShadowView.h"
#include "TestView.h"
#include "Teapot.h"
#define TESTCAM 0


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

static int counter = 0;
static Cube* cube;
static Model3D*object;
//Init server info here later

void Window::initialize(void)
{
	g_pCore->viewmode = viewType::CONSOLE;
	g_pCore->helpMenu = new helpMenu(width, height);
	g_pCore->battlemode = new battleView();
	g_pCore->buildmode = new buildView(width, height);
	g_pCore->menumode = new mainMenu(width, height);
	g_pCore->defaultView = new GameView();

	GameView* view = new GameView();
	//cube = new Cube(1);
	//cube->localTransform.position = Vector3(0, 0, -5);
	//cube->localTransform.scale= Vector3(1, 0.00001, 1);
	//cube->identifier = 1;
	//view->PushGeoNode(cube);
	//Teapot* t = new Teapot(2);

	//set color
	//glColor3f(1, 1, 1);
	cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, -5);
	//cube->localTransform.scale= Vector3(1, 0.00001, 1);
	cube->identifier = 1;
	g_pCore->defaultView->PushGeoNode(cube);

	//object = new Model3D("Hatchet.obj");
	//object->localTransform.position = Vector3(0, 0, -20);
	//object->localTransform.scale = Vector3(1, 1, 1);
	//object->localTransform.rotation = Vector3(0, 0, 0);
	//view->PushGeoNode(object);
	view->PushGeoNode(g_pCore->light);
	//g_pCore->battlemode->PushGeoNode(g_pCore->light);

	Plane* p = new Plane(50);
	p->localTransform.position = Vector3(0, 0, 0);
	view->PushGeoNode(p);
	//g_pCore->battlemode->PushGeoNode(p);
	//t->localTransform.position = Vector3(0, 0, -5);
	//view->PushGeoNode(t);
	//cube2 = new Cube(1);
	//cube2->localTransform.position = Vector3(5, 0, -10);
	//view->PushGeoNode(cube2);

	g_pCore->defaultView = view;
	g_pCore->pGameView = view;
	g_pCore->pPlayer->playerid = 1;

	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.32");

	//Setup the light
	
	Model3D *object = new Model3D("woodcube.obj");
	object->localTransform.position = Vector3(0, 0, -10);
	object->localTransform.scale = Vector3(1, 1, 1);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(object);

	g_pCore->battlemode->PushGeoNode(object);
	g_pCore->battlemode->PushGeoNode(g_pCore->light);
	g_pCore->battlemode->PushGeoNode(p);

	//test shadow view
	//HardShadowView* shadowview = new HardShadowView();
	//g_pCore->pGameView = shadowview;

	//see gui switch and skybox reqs
	g_pCore->skybox = new SkyBox();
	g_pCore->setView();

	//setup camera
	//*g_pCore->pGameView->pViewCamera->position = Vector3(1, 0, 10);

	//setup shader
	//init shader
	//GLuint program = LoadShader("shadow.vert", "shadow.frag");
	//glUseProgram(program);


	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.92.184");
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
	g_pCore->pGameView->VUpdate();

	if (g_pCore->viewmode == viewType::BUILD) {
		viewType s = g_pCore->buildmode->checkTimeOut();
		if (s != g_pCore->viewmode) {
			g_pCore->viewmode = s;
			g_pCore->setView();
		}
	}

    //Call the display routine to draw the cube
    displayCallback();
}
void Window::processNormalKeys(unsigned char key, int x, int y){
	g_pCore->i_pInput->VProcessKeyInput(key, x, y);
	
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
}

void Window::processPassiveMouse(int x, int y) {
	g_pCore->i_pInput->VProcessPassiveMouse(x, y);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    Window::width = w;                                                       //Set the window width
	Window::height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(60.0, double(Window::width) / (double)Window::height, 1, 1000.0); //Set perspective projection viewing frustum
	g_pCore->buildmode->setDimensions(w, h);
	g_pCore->menumode->setDimensions(w, h);
	g_pCore->helpMenu->setDimensions(w, h);
	g_pCore->battlemode->setDimensions(w, h);
	//glFrustum(-1, 1, -1 , 1, 1,5);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.

void Window::displayCallback()
{
	counter = (counter + 1) % 360;
	
	//object->localTransform.rotation.y = counter;
	//Manager get packet	
	GameInfoPacket* p = g_pCore->pGamePacketManager->tryGetGameInfo();
	if (p!=nullptr){
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
	
	if (TESTCAM)
	{
		Matrix4 trans = cube->localTransform.GetRotMatrix4();
		Vector4 forward = Vector4(0, 0, -1, 1);
		Vector4 direction_temp = trans*forward;
		Vector3 direction = Vector3(direction_temp.get_x(), direction_temp.get_y(), direction_temp.get_z());
		direction.normalize();
		printf("direction : %f %f %f\n", direction.x,direction.y,direction.z);
		float distanceToPlayer = 5;
		g_pCore->pGameView->pViewCamera->position = new Vector3(cube->localTransform.position.x - direction.x*distanceToPlayer, cube->localTransform.position.y - direction.y*distanceToPlayer, cube->localTransform.position.z - direction.z*distanceToPlayer);
		g_pCore->pGameView->pViewCamera->rotation = new Vector3(-cube->localTransform.rotation.x, -cube->localTransform.rotation.y, -cube->localTransform.rotation.z);
		//cube2->localTransform.position = Vector3(cube->localTransform.position.x - direction.x*distanceToPlayer, cube->localTransform.position.y - direction.y*distanceToPlayer, cube->localTransform.position.z - direction.z*distanceToPlayer);
		//cube2->localTransform.rotation = Vector3(cube->localTransform.rotation.x, cube->localTransform.rotation.y, cube->localTransform.rotation.z);
	}
	//glPopMatrix();
	//Tell OpenGL to clear any outstanding commands in its command buffer
	//This will make sure that all of our commands are fully executed before
	//we swap buffers and show the user the freshly drawn frame
	glFlush();
	//Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
	glutSwapBuffers();

}
