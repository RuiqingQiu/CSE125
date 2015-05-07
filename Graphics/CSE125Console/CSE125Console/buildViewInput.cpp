#include "stdafx.h"
#include "buildViewInput.h"


buildViewInput::buildViewInput()
{
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



