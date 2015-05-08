#include "stdafx.h"
//#include "GamePacketManager.h"

#include "Shader.h"
#include "GameCore.h"
#include "ShaderSystem.h"
#include "sound.h" // include the sound

#ifndef CSE167_Window_h
#define CSE167_Window_h


class Window	  // OpenGL output window related routines
{
    
public:
	//static viewFactory * factory;
    static int width, height; 	            // window size
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
	static void processMouseClick(int button, int state, int x, int y);
	static void processPassiveMouse(int x, int y);
	static void processMouse(int x, int y);
	static ShaderSystem* shader_system;


};

#endif

