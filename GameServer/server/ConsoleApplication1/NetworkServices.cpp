#include "StdAfx.h"
#include "NetworkServices.h"
#include <stdlib.h>



int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
	int currSize = 0;
	std::string s = std::to_string(messageSize);
	s += "\0";
	char size[11];
	memset(size, 0, 11);
	memcpy(size, s.c_str(), 11);
	int res;
	res = send(curSocket, size, 11,  0);
	if (res < 0) return res;


	while (currSize < messageSize)
	{

		res = send(curSocket, message, messageSize,0);
		if (res < 0)
		{
			return res;
		}
		else
		{
			currSize += res;
		}
	}
	return currSize;
}

int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
	char* messageSize = nullptr;
	if (recv(curSocket, messageSize, 11, 0) != 11)
		return -1;

	int msgSize = std::stoul(messageSize);

	int currSize = 0;
	int res;
	while (currSize < msgSize)
	{

		res = recv(curSocket, buffer, bufSize, 0);
		if (res < 0)
		{
			return res;
		}
		else
		{
			currSize += res;
		}
	}
	return (currSize > bufSize) ? -1 : currSize;
}