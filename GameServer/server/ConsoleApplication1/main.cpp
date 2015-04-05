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
int main()
{

	// initialize the server, comment if running client
	server = new ServerGame();
	
	GameObj* obj = new GameObj(1, 2, 3, 4);
	GameObj* obj2 = new GameObj(8, 7, 6, 5);

	char* des = "wrong";
	server->pushGameObj(*obj);
	server->pushGameObj(*obj2);

	string result = server->convertData(des);
	char cstr [1000000];
	memcpy(cstr, result.c_str(), sizeof(cstr));

	cout << cstr << endl;
	// create thread with arbitrary argument for the run function
	//_beginthread( serverLoop, 0, (void*)12);

	while (1){}

	//Uncomment this part for running client
	// initialize the client 
	//client = new ClientGame();

	//clientLoop();
}

void serverLoop(void * arg)
{
	while (true)
	{
		server->update();
	}
}
