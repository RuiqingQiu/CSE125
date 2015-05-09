#pragma once
#include "stdafx.h"
#include "gui.h"
#include "buildTimer.h"
#include "scoreBox.h"
#include "roboBase.h"
#include "sound.h" //for gui sound effect 

#define MAX_BLOCKS 23
#define GRID_SIZE 5
#define HALF_GRID 2
#define BASE_SIZE 5  //number of objects define base: base 3x3 plus 4 wheels

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);
	~buildView();

	//inherited/override
	virtual void VOnRender();
	virtual void VUpdate();

	virtual viewType mouseClickFunc(int state, int x, int y);
	virtual void keyPressFunc(unsigned char key, int x, int y);
	virtual Vector3 translateNode(Vector3 t, GeoNode * node);
	virtual void setConstraints();

	//buildView only
	void clearConstraints();
	viewType checkTimeOut();
	void rotateRobot(float degrees);

	//leave these public for now, 
	//may need to access to sync to server time/score, etc.
	scrollBox * scroll;
	buildTimer * timer;
	scoreBox * score;
	bool updateview;
	int prevMouseState;

private:
	//intialization helper functions
	void init();
	void createButtons();

	//block adding/removing helper functions
	void addNode();
	void removeNode();
	Vector3 addNewNodePos();
	bool validPos(Vector3 t, GeoNode * node);
	void setCurrentNode(bool adding);
	void setTemplate();  //if template, base or wheel is clicked add imediately instead of waiting for add button click or enter key press

	//for creating a grid for robot size boundaries
	bool setTexture(string filename, GLuint * t);
	GLuint grids[2];

	Vector3 center;
	int selectedType;
	float yRotation;
	int blocksLeft;

	//button pointers for checking special state switch
	button * helpButton;
	button * battleButton;
	bool templateSet;
	numDisplay * blocksDisplay;

	Sound* sound; // for sound effect
};

