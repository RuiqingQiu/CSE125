// CSE125Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graphicsWindow.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);                                      //Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(graphicsWindow::width, graphicsWindow::height);          //Set initial window size
	glutCreateWindow("UCSD CSE 167 - Project 1 - OpenGL Cube"); //Open window and set window title

	glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);                                    //Set shading to smooth

	glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
	glEnable(GL_LIGHTING);                                      //Enable lighting

	//light
	float position[] = { 0.0, 1.0, 0.0, 0.0 };	// lightsource position
	GLfloat  ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0,GL_DIFFUSE,ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glEnable(GL_LIGHT0);
	//mat
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	//Register callback functions:
    glutDisplayFunc(graphicsWindow::displayCallback);
    glutReshapeFunc(graphicsWindow::reshapeCallback);
    glutIdleFunc(graphicsWindow::idleCallback);
    glutKeyboardFunc(graphicsWindow::processNormalKeys);
	//Register the callback for the keyboard
	//Register the callback for the keyboard function keys
	//Register the callback for the mouse
	//Register the callback for the mouse motion
	//Initialize the Window:
	//The body of this function is a great place to load textures, shaders, etc.
	//and do any operations/calculations/configurations that only need to happen once.
    graphicsWindow::initialize();

	//Start up the render loop!
	glutMainLoop();
	return 0;
}

