// main.cpp : Defines the entry point for the console application.
//

// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
#include "ServerGame.h"
// used for multi-threading
#include <process.h>
#include <iostream>
#include "GameObj.h"

void serverLoop(void *);
void clientLoop(void);

ServerGame * server;
unsigned int gameState;
int main()
{

	gameState = 0;
	// initialize the server, comment if running client
	server = new ServerGame();
	
	serverLoop((void*)12);

	//Uncomment this part for running client
	// initialize the client 
	//client = new ClientGame();

	//clientLoop();
}

void serverLoop(void * arg)
{

	while (true)
	{
		switch (gameState){
		case 0: {
					gameState = server->waitForConnections();
					break;
		}
		case 1:
			{
				   //cout << "state 1 " << endl;
				   server->update();
				   
				   //server->sendActionPackets();
				   break;
			}
		}
		//server->update();
	}
}
