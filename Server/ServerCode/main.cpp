// main.cpp : Defines the entry point for the console application.
//

// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
#include "ServerGame.h"
#include "ClientGame.h"
// used for multi-threading
#include <process.h>
#include <iostream>

void serverLoop(void *);
void clientLoop(void);

ServerGame * server;
ClientGame * client;

int main()
{
	
	// initialize the server, comment if running client
	server = new ServerGame();
	while (true)
	{
		server->update();
	}
	// create thread with arbitrary argument for the run function
    //_beginthread( serverLoop, 0, (void*)12);


	//Uncomment this part for running client
    // initialize the client 
    //client = new ClientGame();

	//clientLoop();
}

void serverLoop(void * arg) 
{ 
    while(true) 
    {
        server->update();
    }
}

void clientLoop()
{
    while(true)
    {
        //do game stuff
        client->update();
    }
}
