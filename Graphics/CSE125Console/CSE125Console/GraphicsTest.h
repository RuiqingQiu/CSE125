#pragma once
#ifndef _GraphicsTest
#define _GraphicsTest
#include "GameView.h"
#include "Model3DFactory.h"

class GraphicsTest
{
public:
	GraphicsTest();
	~GraphicsTest();
	void displayTest1(GameView* view);
	void displayTest2(GameView* view);
	void displayTest3(GameView* view);
};
#endif

