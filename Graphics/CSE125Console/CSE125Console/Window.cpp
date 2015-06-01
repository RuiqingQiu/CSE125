#include "stdafx.h"
#include <iostream>

#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

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
#include "ParticleSystem.h"
#define TESTCAM 0

int Window::width  = 1980;   //Set window width in pixels here
int Window::height = 1000;   //Set window height in pixels here

viewFactory * Window::factory; // factory of gui
//static Model3DFactory* m_factory;
ShaderSystem* Window::shader_system;
LightSystem* Window::light_system;
bool Window::build_to_battle = false;
static int counter = 0;
static Cube* cube;
static Fire* fire;
static GraphicsTest* gt;
static Model3D*object;
Sound * Window::soundObject; // static variable

//Init server info here later
Model3D* tmp_object;
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

	CHECK_FRAMEBUFFER_STATUS();

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
	
	light_system = new LightSystem();
	shader_system = new ShaderSystem();
	setupFBO();
	
	
	//m_factory = new  Model3DFactory();
	//g_pCore->skybox = new SkyBox();
	//g_pCore->skybox = new SkyBox("skyboxes/space");
	//g_pCore->skybox = new SkyBox("skyboxes/clouds");
	g_pCore->skybox = new SkyBox("skyboxes/desert");
	//g_pCore->skybox = new SkyBox("skyboxes/city");

	//g_pCore->pPlayer->playerid = 1;
	GameView* view = new GameView();

	//Comment this for non-local testing
	//gt->displayTest4(view);
	//gt->displayTest2(view);
	//gt->displayTest3(view);
	//gt->displayTest1(view);
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

	
	object = Model3DFactory::generateObjectWithType(DESERT);
	object->shader_type = BATTLEFIELD_SHADER;
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = DESERT;
	factory->battlemode->PushEnvironmentNode(object);
	
	
	object = Model3DFactory::generateObjectWithType(BORDER);
	object->shader_type = REGULAR_SHADER;
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BORDER;
	factory->battlemode->PushEnvironmentNode(object);

	
	object = Model3DFactory::generateObjectWithType(STONEHENGE);
	object->shader_type = REGULAR_SHADER;
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = STONEHENGE;
	factory->battlemode->PushEnvironmentNode(object);



	factory->battlemode->PushGeoNode(g_pCore->skybox);
	//factory->viewmode = viewType::MENU;
	factory->viewmode = viewType::MENU;
	factory->setView();
	g_pCore->pGameView = factory->currentView;
	g_pCore->i_pInput = factory->currentInput;

	//Game start with the menu mode

	//gt->displayTest5(factory->battlemode);
	*g_pCore->pGameView->pViewCamera->position = Vector3(0, -40 , -100);
	*g_pCore->pGameView->pViewCamera->rotation = Vector3(20, 0 ,0);
	//Init 6 lights and render them
	light_system->initLights();
	light_system->renderLights(factory->battlemode);

	//factory->battlemode->pViewCamera->FollowingTarget = object;
	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.34");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.92.217");
	//g_pCore->pGamePacketManager->ConnectToServer("137.110.90.86");
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.34");
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.26");

	ParticleSystem* f = new ParticleSystem();
	f->static_object = true;
	f->lifeTime = 10;
	f->maxParticles = 75;
	f->pemissionRate = 0.1;
	f->spawnShape = ParticleInitShape::None;
	f->cylinderRadius = 2;
	f->startColor = Vector3(0.8, 0.8, 0);
	factory->battlemode->PushEnvironmentNode(f);

	factory->battlemode->pViewCamera->FollowingTarget = f;
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

void Window::processNormalKeysUp(unsigned char key, int x, int y)
{
	g_pCore->i_pInput->VProcessKeyInputUp(key, x, y);
	
}

void Window::processSpecialKeys(int key, int x, int y) {
	factory->switchView(key);
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

void Window::processMotion(int x, int y)
{
	g_pCore->i_pInput->VProcessMotion(x, y);
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
	g_pCore->pGameView->pViewCamera->setCamInternals(90.0, double(Window::width) / (double)Window::height, 0.1, 100.0);
	factory->reshapeFunc(w, h);

	//Reshape, set up frame buffer object again based on the new width and height
	setupFBO();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
	clock_t startTime = clock();

	// play the background music through out the whole game, may change with the view
	if (factory->currentView == factory->menumode || factory->currentView == factory->defaultView){
		if (factory->menumode->playPressed){
			soundObject->playLoading();
		}
		else{
			soundObject->playOpening();
		}
	}

	// if in build mode play build view background music
	else if (factory->currentView == factory->buildmode){
		soundObject->playBuildViewBackground();
	}
	else if (factory->currentView == factory->battlemode){
		soundObject->playMusic();
	}
	// play the ending sound
	else if (factory->currentView == factory->gameOver){
		soundObject->playEnding();
	}

	//object->localTransform.rotation.y = counter;
	//Manager get packet	

	//Every frame, first update the objects from server infos
	GameInfoPacket* p = g_pCore->pGamePacketManager->tryGetGameInfo();
	

	if (p!=nullptr) {
		printf("number of game objects: %i\n number of events: %i\n", p->player_infos.size(), p->event_infos.size());

		switch (p->packet_types){
			case GAME_STATE:{
				//Update states in the actual battle mode
				factory->battlemode->VOnClientUpdate(p);
				//g_pCore->pGameView->VOnClientUpdate(p);
				g_pCore->pEventSystem->ProcessGamePacket(p);
				break;
			}
			case CONFIRM_CONNECTION:{
				g_pCore->pPlayer->playerid = p->player_infos[0]->id;
				//This is for testing
				g_pCore->pGameView->pPlayer = g_pCore->pPlayer;
				//This is real for battle mode player info
				factory->battlemode->pPlayer = g_pCore->pPlayer;
				//cout << "player id " << p->player_infos[0]->id << endl;

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
	
	//Send keyboard event, will put it to somewhere else 5/19/15
	if (factory->viewmode == viewType::BATTLE){
		if (g_pCore->i_pInput->keyStates['a'] == true){
			g_pCore->pGamePacketManager->SendMoveToLeft(g_pCore->pPlayer->playerid);
		}
		if (g_pCore->i_pInput->keyStates['w'] == true){
			g_pCore->pGamePacketManager->SendMoveToForward(g_pCore->pPlayer->playerid);
		}
		if (g_pCore->i_pInput->keyStates['s'] == true){
			g_pCore->pGamePacketManager->SendMoveToBackward(g_pCore->pPlayer->playerid);
		}

		if (g_pCore->i_pInput->keyStates['d'] == true){
			g_pCore->pGamePacketManager->SendMoveToRight(g_pCore->pPlayer->playerid);
		}
	}

	//Draw everything
	//g_pCore->pGameView->VOnRender();
	factory->currentView->VOnRender();
	glFlush();
	glutSwapBuffers();
	clock_t endTime = clock();
	cout << "frame rate: " << 1.0 / (float((endTime - startTime)) / CLOCKS_PER_SEC) << endl;

	//gt->displayTest5(factory->battlemode);
	//factory->battlemode->pViewCamera->FollowingTarget = f;
}
