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
#include "SkyBox.h"


#define TESTCAM 1


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

gui buildmode = gui();


static Cube* cube;
//Init server info here later
void Window::initialize(void)
{
	//set color
	//glColor3f(1, 1, 1);
	GameView* view = new GameView();
	cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, 0);
	//cube->localTransform.scale= Vector3(1, 0.00001, 1);
	cube->identifier = 1;
	view->PushGeoNode(cube);
	
	g_pCore->pGameView = view;
	//g_pCore->pPlayer->playerid = 1;

	//g_pCore->pGamePacketManager->ConnectToServer("137.110.91.84");

	//Setup the light
	//Model3D *object = new Model3D("woodcube.obj");
	//object->localTransform.position = Vector3(0, 0, 0);
	//object->localTransform.scale = Vector3(1, 1, 1);
	//object->localTransform.rotation = Vector3(90, 0, 0);

	//view->PushGeoNode(object);


	SkyBox *object2 = new SkyBox();
	view->PushGeoNode(object2);

	//setup camera
	*g_pCore->pGameView->pViewCamera->position = Vector3(1, 0, 5);
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

	
	if (TESTCAM){
		if (key == ','){
			cube->localTransform.rotation.y += 1;
		}
		else if (key == '.'){
			cube->localTransform.rotation.y -= 1;
		}
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

	buildmode.draw(width, height);

	//test for camera
	
	if (TESTCAM)
	{
		Matrix4 trans = cube->localTransform.GetMatrix4();
		trans.print("transformation matrix, ");
		Vector4 forward = Vector4(0, 0, -1, 1);
		Vector4 direction = trans*forward;
		printf("dir : %f %f %f\n", direction.x , direction.y,direction.z);
		float distanceToPlayer = 20;
		g_pCore->pGameView->pViewCamera->position = new Vector3(cube->localTransform.position.x - direction.x*distanceToPlayer, cube->localTransform.position.y - direction.y*distanceToPlayer, cube->localTransform.position.z - direction.z*distanceToPlayer);
		
		printf("pos : %f %f %f\n", g_pCore->pGameView->pViewCamera->position->x, g_pCore->pGameView->pViewCamera->position->y, g_pCore->pGameView->pViewCamera->position->z);

		g_pCore->pGameView->pViewCamera->rotation = new Vector3(-cube->localTransform.rotation.x, -cube->localTransform.rotation.y, -cube->localTransform.rotation.z);
	}
	

}
