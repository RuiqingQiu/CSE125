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
#include "Grass.h"
#include "GraphicsTest.h"
#define TESTCAM 0

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

static viewFactory * factory; // factory of gui
//static Model3DFactory* m_factory;
ShaderSystem* Window::shader_system;
static int counter = 0;
static Cube* cube;
static Fire* fire;
static GraphicsTest* gt;
static Model3D*object;
static Sound *soundObject;
//Init server info here later



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

//Helper function for split strings
unsigned int split2(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos));

	return strs.size();
}



void Window::initialize(void)
{
	m_factory = new  Model3DFactory(); //must call before making view factory
	factory = new viewFactory(width, height);

	// Initialize the Sound object
	soundObject = new Sound();

	
	//factory = new viewFactory(true);  //for no gui
	
	//Shader part
	gt = new GraphicsTest();
	
	shader_system = new ShaderSystem();
	setupFBO();
	
	
	//m_factory = new  Model3DFactory();
	//g_pCore->skybox = new SkyBox();
	//g_pCore->skybox = new SkyBox("skyboxes/space");
	g_pCore->skybox = new SkyBox("skyboxes/clouds");
	//g_pCore->pPlayer->playerid = 1;
	GameView* view = new GameView();

	//Comment this for non-local testing
	gt->displayTest1(view);
	//GameView* view = new HardShadowView();
	view->PushGeoNode(g_pCore->skybox);
	//Teapot* t = new Teapot(2);

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			float ri = (rand() % 10 - 5) * 0.001;
			float rj = (rand() % 10 - 5) * 0.001;
			Grass * grass = new Grass();
			grass->localTransform.position = Vector3(i*0.1 - 2 + ri, -1, j*0.1 - 2 + rj);
			grass->localTransform.rotation = Vector3(0, 0, 0);
			view->PushGrassNode(grass);
		}
	}
	//////////////////////////
	/*
	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = EDGE_SHADER;
	object->edge_highlight = true;
	view->num_of_objs_highlight++;
	object->localTransform.position = Vector3(0, 0, -17);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = BLUR_SHADER;
	object->blur = true;
	view->num_of_objs_blur++;
	object->localTransform.position = Vector3(-3, 0, -17);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(CrystalCube);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(3, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(TREE1);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(TREE2);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-5, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(TREE3);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(5, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = true;
	view->PushEnvironmentNode(object);
	*/
	object = Model3DFactory::generateObjectWithType(BATTLEFIELDOUTER);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(0, -2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->auto_rotate = false;
	view->PushEnvironmentNode(object);
	///////////////////////////
	object = Model3DFactory::generateObjectWithType(BATTLEFIELDINNER);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(0, -2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->type = BATTLEFIELD;
	//factory->battlemode->PushGeoNode(object);
	view->PushEnvironmentNode(object);
	
	factory->battlemode->PushGeoNode(g_pCore->skybox);
	
	factory->defaultView = view;
	factory->setView();
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;

	*g_pCore->pGameView->pViewCamera->position = Vector3(0, 0, 10);
	
	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.34");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.92.217");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.90.86");
	g_pCore->pGamePacketManager->ConnectToServer("128.54.70.27");
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
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum
	//glFrustum(-1, 1, -1 , 1, 1,5);
	g_pCore->pGameView->pViewCamera->setCamInternals(90.0, double(Window::width) / (double)Window::height, 0.1, 30.0);
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
				//Update states in the actual battle mode
				//factory->battlemode->VOnClientUpdate(p);
				g_pCore->pGameView->VOnClientUpdate(p);
				g_pCore->pEventSystem->ProcessGamePacket(p);
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
