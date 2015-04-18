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

//gui buildmode = gui();
static Vector4 light = Vector4(0.0, 0.0, 5.0, 0.0);
static int counter = 0;
static Cube* cube;
static Cube* cube2;
static Model3D*object;
//Init server info here later

/*
// Loading shader function
GLhandleARB loadShader1(char* filename, unsigned int type)
{
	FILE *pfile;
	GLhandleARB handle;
	const GLcharARB* files[1];

	// shader Compilation variable
	GLint result;				// Compilation code result
	GLint errorLoglength;
	char* errorLogText;
	GLsizei actualErrorLogLength;

	char buffer[400000];
	memset(buffer, 0, 400000);

	// This will raise a warning on MS compiler
	pfile = fopen(filename, "rb");
	if (!pfile)
	{
		printf("Sorry, can't open file: '%s'.\n", filename);
		exit(0);
	}

	fread(buffer, sizeof(char), 400000, pfile);
	//printf("%s\n",buffer);


	fclose(pfile);

	handle = glCreateShaderObjectARB(type);
	if (!handle)
	{
		//We have failed creating the vertex shader object.
		printf("Failed creating vertex shader object from file: %s.", filename);
		exit(0);
	}

	files[0] = (const GLcharARB*)buffer;
	glShaderSourceARB(
		handle, //The handle to our shader
		1, //The number of files.
		files, //An array of const char * data, which represents the source code of theshaders
		NULL);

	glCompileShaderARB(handle);

	//Compilation checking.
	glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &result);

	// If an error was detected.
	if (!result)
	{
		//We failed to compile.
		printf("Shader '%s' failed compilation.\n", filename);

		//Attempt to get the length of our error log.
		glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &errorLoglength);

		//Create a buffer to read compilation error message
		errorLogText = (char*)malloc(sizeof(char)* errorLoglength);

		//Used to get the final length of the log.
		glGetInfoLogARB(handle, errorLoglength, &actualErrorLogLength, errorLogText);

		// Display errors.
		printf("%s\n", errorLogText);

		// Free the buffer malloced earlier
		free(errorLogText);
	}
	printf("Shader loaded done\n");
	return handle;
}*/

void Window::initialize(void)
{
	//TestView* v = new TestView();
	//g_pCore->pGameView = v;
	//set color
	//glColor3f(1, 1, 1);
	
	GameView* view = new GameView();
	cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, -5);
	//cube->localTransform.scale= Vector3(1, 0.00001, 1);
	cube->identifier = 1;
	//view->PushGeoNode(cube);
	Teapot* t = new Teapot(2);

	object = new Model3D("Hatchet.obj");
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.scale = Vector3(1, 1, 1);
	object->localTransform.rotation = Vector3(0, 90, 0);
	view->PushGeoNode(object);

	/*
	GLhandleARB vertexShaderHandle;
	GLhandleARB fragmentShaderHandle;

	vertexShaderHandle = loadShader1("shadow.vert", GL_VERTEX_SHADER);
	fragmentShaderHandle = loadShader1("shadow.frag", GL_FRAGMENT_SHADER);

	GLhandleARB shader_id = glCreateProgramObjectARB();

	glAttachObjectARB(shader_id, vertexShaderHandle);
	glAttachObjectARB(shader_id, fragmentShaderHandle);
	glLinkProgramARB(shader_id);



	

	glUseProgramObjectARB(shader_id);


	GLuint texturaID[2];
	glGenTextures(2, texturaID);
	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, texturaID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Albedo.PNG", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	

	glBindTexture(GL_TEXTURE_2D, texturaID[1]);
	image = SOIL_load_image("Normal_Clrear.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturaID[1]);

	glUniform1i(glGetUniformLocation(shader_id, "tex"), 0);
	glUniform1i(glGetUniformLocation(shader_id, "norm"), 1);

	*/










	/*
	GLuint textures[1];
	glGenTextures(0, textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shader_id , "texKitten"), 0);
	*/










	t->localTransform.position = Vector3(0, 0, -5);
	//view->PushGeoNode(t);
	//cube2 = new Cube(1);
	//cube2->localTransform.position = Vector3(5, 0, -10);
	//view->PushGeoNode(cube2);

	g_pCore->pGameView = view;
	g_pCore->pPlayer->playerid = 1;
	
	//default to console view
	
	g_pCore->viewmode = guiType::CONSOLE;
	g_pCore->helpMenu = new gui();
	g_pCore->battlemode = new gui();
	g_pCore->buildmode = new buildView(width, height);
	g_pCore->menumode = new mainMenu(width, height);
	g_pCore->defaultGui = new gui();

	if (g_pCore->viewmode == guiType::CONSOLE) {
		g_pCore->gameGui = g_pCore->defaultGui;
		g_pCore->i_pInput = g_pCore->standard_Input;
	}
	else if (g_pCore->viewmode == guiType::BUILD) {
		g_pCore->gameGui = g_pCore->buildmode;
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::BATTLE) {
		g_pCore->gameGui = g_pCore->battlemode;
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::HELP) {
		g_pCore->gameGui = g_pCore->helpMenu;
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	// main menu view
	else if (g_pCore->viewmode == guiType::MENU) {
		g_pCore->gameGui = g_pCore->menumode;
		g_pCore->i_pInput = g_pCore->gui_Input;
	}

	//connect to server
	//g_pCore->pGamePacketManager->ConnectToServer("128.54.70.32");

	//Setup the light
	
	//Model3D *object = new Model3D("woodcube.obj");
	//object->localTransform.position = Vector3(0, 0, -10);
	//object->localTransform.scale = Vector3(1, 1, 1);
	//object->localTransform.rotation = Vector3(0, 0, 0);
	//view->PushGeoNode(object);

	//test shadow view
	//HardShadowView* shadowview = new HardShadowView();
	//g_pCore->pGameView = shadowview;

	//see comments about switching views in gameCore.cpp
	g_pCore->skybox = new SkyBox();
	//only need skybox for battle mode and console mode right now
	if (g_pCore->viewmode == guiType::CONSOLE ||
		g_pCore->viewmode == guiType::BATTLE) {
		view->PushGeoNode(g_pCore->skybox);
	}
	
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


void Window::processMouseClick(int button, int state, int x, int y) {
	g_pCore->i_pInput->VProcessMouseClick(button, state, x, y);
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
	gluPerspective(60.0, double(Window::width) / (double)Window::height, 10, 1000.0); //Set perspective projection viewing frustum
	//g_pCore->buildmode->setDimensions(w, h);
	//g_pCore->menumode->setDimensions(w, h);
	//g_pCore->helpMenu->setDimensions(w, h);
	//g_pCore->battlemode->setDimensions(w, h);
	
	//glFrustum(-1, 1, -1 , 1, 1,5);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.

void Window::displayCallback()
{
	counter = (counter + 1) % 360;
	
	Matrix4 rot;
	rot.makeRotateY(-counter);
	light = rot * light;
	light.print("light");
	//float LightPosition[] = { light.x, light.y, light.z };
	float LightPosition[] = { 0, 5, 0 };

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	//glEnable(GL_LIGHT0);

	object->localTransform.rotation = Vector3(0, counter, 0);
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

	//cout << "on display " << endl;
	g_pCore->pGameView->VOnRender();

	//g_pCore->gameGui->VOnRender();


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
