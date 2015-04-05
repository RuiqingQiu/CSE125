#include "stdafx.h"
#include "GameView.h"


GameView::GameView()
{
}


GameView::~GameView()
{
}


void GameView::OnRender()
{
	for each (GeoNode* node in NodeList)
	{
		node->VOnDraw();
	}
}

void GameView::OnClientUpdate(GameInfoPacket* info)
{
	for each (GeoNode* node in NodeList)
	{
	    node->VOnClientUpdate(info);
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