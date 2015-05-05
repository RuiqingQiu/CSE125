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
#include "Fire.h"
#include "tiny_obj_loader.h"
#include "Model3D.h"
#include "SkyBox.h"
#include "Plane.h"
#include "HardShadowView.h"
#include "TestView.h"
#include "Teapot.h"
#include "Model3DFactory.h"
#include "sound.h" // include the sound
#include "Grass.h"
#define TESTCAM 1


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

static viewFactory * factory; // factory of gui
static Model3DFactory* m_factory;
ShaderSystem* Window::shader_system;
static int counter = 0;
static Cube* cube;
static Fire* fire;

static Model3D*object;
static Sound *soundObject;

void CHECK_FRAMEBUFFER_STATUS()
{
	GLenum status;
	status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	switch (status) {
	case GL_FRAMEBUFFER_COMPLETE:
		cout << "frame buffer complete" << endl;
		break;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		/* choose different formats */
		cout << "frame buffer not supported" << endl;

		break;

	default:
		/* programming error; will fail on all hardware */
		fputs("Framebuffer Error\n", stderr);
		exit(-1);
	}
}

void setupFBO(){
	glGenFramebuffers(1, &Window::shader_system->fb);
	glGenTextures(1, &Window::shader_system->color);
	glGenRenderbuffers(1, &Window::shader_system->depth);

	glBindFramebuffer(GL_FRAMEBUFFER, Window::shader_system->fb);

	glBindTexture(GL_TEXTURE_2D, Window::shader_system->color);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		Window::width, Window::height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Window::shader_system->color, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, Window::shader_system->depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Window::width, Window::height);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
		GL_RENDERBUFFER, Window::shader_system->depth);

	//CHECK_FRAMEBUFFER_STATUS();

	//Switch back to default 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


void Window::initialize(void)
{
	factory = new viewFactory(width, height);
	
	//factory = new viewFactory(true);  //for no gui
	
	//Shader part
	shader_system = new ShaderSystem();
	setupFBO();
	
	
	m_factory = new  Model3DFactory();
	//g_pCore->skybox = new SkyBox();
	//g_pCore->skybox = new SkyBox("skyboxes/space");
	g_pCore->skybox = new SkyBox("skyboxes/clouds");
	//g_pCore->pPlayer->playerid = 1;
	GameView* view = new GameView();
	//GameView* view = new HardShadowView();
	view->PushGeoNode(g_pCore->skybox);
	//Teapot* t = new Teapot(2);

	// Initialize the Sound object
	soundObject = new Sound();

	//set color
	//glColor3f(1, 1, 1);
	/*
	cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, 0);
	cube->localTransform.rotation= Vector3(-180, 40, 40);
	cube->identifier = 1;
	view->PushGeoNode(cube);
	view->pViewCamera->FollowingTarget = cube;
	*/
	
	/*
	object = Model3DFactory::generateObjectWithType(Discount);
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.scale = Vector3(1, 1, 1);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(object);
	
	object = Model3DFactory::generateObjectWithType(Needle);
	object->localTransform.position = Vector3(-3, 0, -20);
	object->localTransform.scale = Vector3(1, 1, 1);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(object);
	*/
	/*
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			object = Model3DFactory::generateObjectWithType(BasicCube);
			object->localTransform.position = Vector3(i, -2, j);
			object->localTransform.scale = Vector3(1, 1, 1);
			object->localTransform.rotation = Vector3(0, 0, 0);

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			float ri = (rand() % 10 - 5) * 0.001;
			float rj = (rand() % 10 - 5) * 0.001;
			Grass * grass = new Grass();
			grass->localTransform.position = Vector3(i*0.1 - 2 + ri, 1, j*0.1 - 2 + rj);
			grass->localTransform.rotation = Vector3(0, 0, 0);
			view->PushGrassNode(grass);
		}
	}
	/*
	object = Model3DFactory::generateObjectWithType(BLOCKYGUN);
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGeoNode(object);
	*/
	
	object = Model3DFactory::generateObjectWithType(BATTLEFIELD);
	object->localTransform.position = Vector3(0, -2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	view->PushGrassNode(object);
	
	//set color
	//glColor3f(1, 1, 1);
	/*.
	*/

	factory->battlemode->PushGeoNode(g_pCore->skybox);
	factory->battlemode->PushGeoNode(g_pCore->light);
	
	factory->defaultView = view;
	factory->setView();
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;

	*g_pCore->pGameView->pViewCamera->position = Vector3(0, 0, 10);
	
	//connect to server

	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.32");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.92.217");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.91.53");
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.14");
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.30");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.92.217");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.90.168");
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.35");
	
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.90.86");
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
	factory->keyboardFunc(key, x, y);
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;
	
	if (TESTCAM){
		if (key == ','){
			cube->localTransform.rotation.x += 30;
		}
		else if (key == '.'){
			cube->localTransform.rotation.x -= 30;
		}
	}

	if (TESTCAM){
		if (key == 'l'){
			cube->localTransform.rotation.z += 30;
		}
		else if (key == ';'){
			cube->localTransform.rotation.z -= 30;
		}
		// if the key is 1, play the sound
		else if (key == '1'){
			/*
			// Load a sound buffer from a wav file
			sf::SoundBuffer buffer;
			sf::Sound sound;
			if(!buffer.loadFromFile("Payback.wav"))
				cout << "ERROR!" << endl;
			// Create a sound instance and play it
			sound.setBuffer(buffer);
			sound.play();
			sound.setLoop(true); // the music will loop itself when ends
			// Loop while the sound is playing
			while (sound.getStatus() == sf::Sound::Playing)
			{
				// Leave some CPU time for other processes
				sf::Time t1 = sf::seconds(0.1f);
				sf::sleep(t1);
				// Display the playing position
				cout << "\rPlaying... " << endl;
			}
		*/
			
		}
	}
}

void Window::processSpecialKeys(int key, int x, int y) {
	g_pCore->i_pInput->VProcessSpecialKey(key, x, y);
}

void Window::processMouse(int x, int y)
{
	g_pCore->i_pInput->VProcessMouse(x, y);
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
	gluPerspective(60.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum
	//glFrustum(-1, 1, -1 , 1, 1,5);
	g_pCore->pGameView->pViewCamera->setCamInternals(60.0, double(Window::width) / (double)Window::height, 0.1, 30.0);
	factory->reshapeFunc(w, h);

	//Reshape, set up frame buffer object again based on the new width and height
	setupFBO();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.

void Window::displayCallback() {
	clock_t startTime = clock();
	// play the background music through out the whole game
	soundObject->playMusic();

	//object->localTransform.rotation.y = counter;
	//Manager get packet	

	//Every frame, first update the objects from server infos
	GameInfoPacket* p = g_pCore->pGamePacketManager->tryGetGameInfo();
	if (p!=nullptr) {
		switch (p->packet_types){
			case GAME_STATE:{
				g_pCore->pGameView->VOnClientUpdate(p);
				break;
			}
			case CONFIRM_CONNECTION:{
				g_pCore->pPlayer->playerid = p->player_infos[0]->id;
				g_pCore->pGameView->pPlayer = g_pCore->pPlayer;
				cout << "player id " << p->player_infos[0]->id << endl;

				break;
			}
			default:{
				break;
			}
		}
		//clean memory
		for each (PlayerInfo* pi in p->player_infos)
		{
			delete(pi);
		}
		delete(p);
	}
	
	//Draw everything
	g_pCore->pGameView->VOnRender();
	glFlush();
	glutSwapBuffers();
	clock_t endTime = clock();
	//cout << "frame rate: " << 1.0 / (float((endTime - startTime)) / CLOCKS_PER_SEC) << endl;
}
