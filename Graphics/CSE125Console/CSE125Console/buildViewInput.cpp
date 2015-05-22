#include "stdafx.h"
#include "buildViewInput.h"


buildViewInput::buildViewInput()
{
	leftDown = false;
	rightDown = false;
	prevX = 0;
	prevY = 0;
}


buildViewInput::~buildViewInput()
{
}

void buildViewInput::VProcessKeyInput(unsigned char key, int x, int y) {
	g_pCore->pGameView->keyPressFunc(key, x, y);
	if (g_pCore->pGameView->currentNode == nullptr) return;
	Vector3 newPos = g_pCore->pGameView->currentNode->localTransform.position;
	switch (key) {
		//move the new block to be added to the robot
	case 's':
		newPos = g_pCore->pGameView->translateNode(Vector3(0, 0, 1), g_pCore->pGameView->currentNode);
		break;
	case 'w':
		newPos = g_pCore->pGameView->translateNode(Vector3(0, 0, -1), g_pCore->pGameView->currentNode);
		break;
	case 'a':
		newPos = g_pCore->pGameView->translateNode(Vector3(-1, 0, 0), g_pCore->pGameView->currentNode);
		break;
	case 'd':
		newPos = g_pCore->pGameView->translateNode(Vector3(1, 0, 0), g_pCore->pGameView->currentNode);
		break;
	case 'r':
		g_pCore->pGameView->pViewCamera->resetPolar();
		break;
	default:
		break;
	}
	g_pCore->pGameView->currentNode->localTransform.position = newPos;
	g_pCore->pGameView->setConstraints();
}

void buildViewInput::VProcessSpecialKey(int key, int x, int y) {
	if (g_pCore->pGameView->currentNode == nullptr) return;
	switch (key) {
		//move the new block to be added to the robot
	case GLUT_KEY_LEFT:
		g_pCore->pGameView->currentNode->localTransform.rotation.y += 90;
		break;
	case GLUT_KEY_RIGHT:
		g_pCore->pGameView->currentNode->localTransform.rotation.y -= 90;
		break;
	case GLUT_KEY_DOWN:
		g_pCore->pGameView->currentNode->localTransform.rotation.x += 45;
		break;
	case GLUT_KEY_UP:
		g_pCore->pGameView->currentNode->localTransform.rotation.x -= 45;
		break;
	default:
		break;
	}
}

void buildViewInput::VProcessMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		leftDown = (state == GLUT_DOWN);
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		rightDown = (state == GLUT_DOWN);
	}
}

void buildViewInput::VProcessPassiveMouse(int x, int y) {
	int dx = x - prevX;
	int dy = -(y - prevY);

	prevX = x;
	prevY = y;

	if (leftDown) {
		g_pCore->pGameView->pViewCamera->updatePolar(dx, dy, 1);
	}

	if (rightDown) {
		g_pCore->pGameView->pViewCamera->updatePolar(0, 0, 1.0 - (dx*0.01) );
	}
}

void buildViewInput::VProcessMotion(int x, int y) {
	VProcessPassiveMouse(x, y);
}



