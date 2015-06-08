#include "StdAfx.h"
#include "NetworkServices.h"
#include <iostream>

int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
	//timeval timeout;
	//fd_set fds;
	//FD_ZERO(&fds);
	//FD_SET(curSocket, &fds);
	//int selectResult = select(0, &fds, 0, 0, &timeout);
	//if (selectResult != 0) {
	//	std::cout << "Stalling in Send, selectResult: " << selectResult << std::endl;

	//	return 0;
	//}
	//else
	//{
		return send(curSocket, message, messageSize, 0);
	//}
}

int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
	//timeval timeout;
	//fd_set fds;
	//FD_ZERO(&fds);
	//FD_SET(curSocket, &fds);
	//int selectResult = select(0, &fds, 0, 0, &timeout);
	//if (selectResult != 1) {
	//	std::cout << "Nothing in Receive, selectResult: " << selectResult << std::endl;
	//	return 0;
	//}
	//else
	//{
		return recv(curSocket, buffer, bufSize, 0);
	//}
	
}




//int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
//{
//	int currSize = 0;
//	std::string s = std::to_string(messageSize); 
//		std::cout << "send" << std::endl;
//	std::cout << "msg size: " << messageSize << std::endl;
//	std::cout << "message: " << message << std::endl;
//	s += "\0";
//	char size[11];
//	memset(size, 0, 11);
//	memcpy(size, s.c_str(), 11);
//	int res;
//	res = send(curSocket, size, 11, 0);
//	if (res < 0) return res;
//
//
//	while (currSize < messageSize)
//	{
//
//		res = send(curSocket, &message[currSize], messageSize - currSize, 0);
//		if (res < 0)
//		{
//			return res;
//		}
//		else
//		{
//			currSize += res;
//			std::cout << "sent msg of size: " << res << std::endl;
//		}
//		std::cout << "currSize: " << currSize << std::endl;
//	}
//	return currSize;
//}
//
//int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
//{
//	std::cout << "receive" << std::endl;
//	char* messageSize = nullptr;
//	int result = recv(curSocket, messageSize, 11, 0);
//	std::cout << "result: " << result << std::endl;
//	if (messageSize != nullptr)
//	{
//		std::cout << "messageSize: " << messageSize << std::endl;
//	}
//	if (result != 11)
//		return -1;
//
//	int msgSize = std::stoul(messageSize);
//
//	std::cout << "msg size: " << msgSize << std::endl;
//	int currSize = 0;
//	int res;
//	while (currSize < msgSize)
//	{
//
//		res = recv(curSocket, &buffer[currSize], bufSize-currSize, 0);
//		if (res < 0)
//		{
//			return res;
//		}
//		else
//		{
//			currSize += res;
//			std::cout << "received msg of size: " << res << std::endl;
//		}
//		std::cout << "currSize: " << currSize << std::endl;
//	}
//	std::cout << "msg buffer: " << buffer << std::endl;
//	return (currSize > bufSize) ? -1 : currSize;
//}