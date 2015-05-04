#pragma once
#include "stdafx.h"
#include "gui.h"
#include "buildTimer.h"
#include "scoreBox.h"
#include "roboBase.h"

#define MAX_BLOCKS 23
#define GRID_SIZE 5
#define HALF_GRID 2
#define BASE_SIZE 5  //number of objects define base: base 3x3 plus 4 wheels

class buildView : public gui {
public:
	buildView();
	buildView(int w, int h);

	void VOnRender();
	void VUpdate();
	void createButtons();

	viewType mouseClickFunc(int state, int x, int y);
	virtual void keyPressFunc(unsigned char key, int x, int y);

	viewType checkTimeOut();

	virtual Vector3 translateNode(Vector3 t, GeoNode * node);
	Vector3 addNewNodePos();
	bool validPos(Vector3 t, GeoNode * node);

	virtual void setConstraints();
	void clearConstraints();

	~buildView();

	vector<button*> listItems;
	Vector3 center;
	scrollBox * scroll;
	buildTimer * timer;
	scoreBox * score;
	bool updateview;
	float yRotation;
	Matrix4 rotateY;
	int prevMouseState;

private:
	void addNode();
	void removeNode();
	bool setTexture(string filename, GLuint * t);

	GLuint grids[2];

	int selectedType;
};

