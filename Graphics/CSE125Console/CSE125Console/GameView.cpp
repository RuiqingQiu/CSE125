#include "stdafx.h"
#include "GameView.h"


GameView::GameView()
{
	pViewCamera = new Camera();
}


GameView::~GameView()
{
}


void GameView::VOnRender()
{
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	pViewCamera->setUpCamera();
	
	

	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());

	for each (GeoNode* node in NodeList)
	{
		node->VOnDraw();
	}

	//glPopMatrix();
	//Tell OpenGL to clear any outstanding commands in its command buffer
	//This will make sure that all of our commands are fully executed before
	//we swap buffers and show the user the freshly drawn frame
	//glFlush();
	//Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
	//glutSwapBuffers();
}

void GameView::VOnClientUpdate(GameInfoPacket* info)
{
	for each (GeoNode* node in NodeList)
	{
	    node->VOnClientUpdate(info);
	}
	//Loop through the list to see anything that's not being processed. if so, create
	for (int i = 0; i < info->player_infos.size(); i++){
		if (!info->player_infos[i]->processed){
			double x = info->player_infos[i]->x;
			double y = info->player_infos[i]->y;
			double z = info->player_infos[i]->z;
			cout << "data is not processed, need to create objects" << endl;
			Cube* cube = new Cube(1);
			cube->localTransform.position = Vector3(x, y, z);
			cube->identifier = info->player_infos[i]->id;
			NodeList.push_back(cube);
		}
	}
}

void GameView::PushGeoNode(GeoNode* node)
{
	NodeList.push_back(node);
}

void GameView::PopGeoNode(GeoNode* m_node)
{
	for (int i = 0; i < NodeList.size(); i++)
	{
		if (NodeList[i] == m_node)
		{
			NodeList.erase(NodeList.begin() + i);
		}
	}
}