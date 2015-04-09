// main.cpp : Defines the entry point for the console application.
//
//#include "TimeFrame.h"
// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
// used for multi-threading
#include <process.h>
#include <ctime>
#include "GameObj.h"
#include "serverCore.h"
#include "definition.h"
#include <btBulletDynamicsCommon.h>

void serverLoop(void *);
void clientLoop(void);

ServerCore * serverCore;

int main()
{
	btBoxShape *b = new btBoxShape(btVector3(0, 0, 0));
	serverCore = new ServerCore();
	serverCore->serverLoop();

}

