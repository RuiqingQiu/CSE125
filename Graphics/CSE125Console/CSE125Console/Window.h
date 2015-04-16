#include "stdafx.h"
//#include "GamePacketManager.h"

#include "Shader.h"
#include "mainmenu.h"

#include "GameCore.h"
#include "buildView.h"

#ifndef CSE167_Window_h
#define CSE167_Window_h

class Window	  // OpenGL output window related routines
{
    
public:

    static int width, height; 	            // window size
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processMouseClick(int button, int state, int x, int y);
};

#endif

