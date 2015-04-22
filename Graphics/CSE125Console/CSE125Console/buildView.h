#pragma once
#include "stdafx.h"
#include "gui.h"
#include "buildTimer.h"
#include "scoreBox.h"
#include "Cube.h"

#define MAX_BLOCKS 27
#define GRID_SIZE 5
#define HALF_GRID 2

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

	~buildView();

	vector<button*> listItems;
	Vector3 center;
	scrollBox * scroll;
	buildTimer * timer;
	scoreBox * score;
	bool updateview;
	bool mappings[MAX_BLOCKS];
	int currentBlock;

private:
	void addNode();
	void removeNode();

	int prevMouseState;
};

