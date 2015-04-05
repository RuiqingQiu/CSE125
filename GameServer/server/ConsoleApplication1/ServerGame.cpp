#include "StdAfx.h"
#include "ServerGame.h"

unsigned int ServerGame::client_id;

ServerGame::ServerGame(void)
{
	// id's to assign clients for our table
	client_id = 0;


	// set up the server network to listen 
	network = new ServerNetwork();

}

ServerGame::~ServerGame(void)
{
}

void ServerGame::update()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		client_id++;
	}

	receiveFromClients();
}

void ServerGame::receiveFromClients()
{

	CPacket packet;

	// go through all clients
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(CPacket);

			switch (packet.packet_type) {

			case INIT_CONNECTION:

				printf("server received init packet from client\n");
				sendActionPackets();

				break;

			case GAME_STATE:

				printf("server received action event packet from client\n");
				sendActionPackets();

				break;

			default:
				sendActionPackets();

				printf("error in packet types\n");

				break;
			}
		}
	}
}


void ServerGame::sendActionPackets()
{

	cout << "send" << endl;
	// send action packet
	const unsigned int packet_size = sizeof(SPacket);
	char packet_data[packet_size];

	//GameObj* obj = new GameObj(1, 2, 3, -12);
	//GameObj* obj2 = new GameObj(8, 7, 6, -5);

	SPacket packet;
	//packet.data[0] = '1';

	//char* des = "wrong";
	//this->pushGameObj(*obj);
	//this->pushGameObj(*obj2);
	float x = (float)rand() / RAND_MAX;
	string result = "1 " + to_string(x) + " 0 -5\n";

	//string result = this->convertData(des);
	memcpy(packet.data, result.c_str(), sizeof(packet.data));

	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}
/*
// convert gameobjs to jason file
string ServerGame::convertData(char* des){
	string temp;
	for (vector<GameObj>::iterator i = gameObjs.begin();
		i != gameObjs.end(); ++i)
	{
		temp += to_string(i->getId());
		temp += ' ';
		temp += to_string(i->getX());
		temp += ' ';
		temp += to_string(i->getY());
		temp += ' ';
		temp += to_string(i->getZ());
		temp += '\n';
	}
	return temp;
	des = new char[temp.length() + 1];
	memset(des, 0, temp.length() + 1);
	memcpy(des, temp.c_str(), temp.length());
}

std::vector<GameObj> ServerGame::getGameObjs()
{
	return gameObjs;
}

void ServerGame::pushGameObj(GameObj obj)
{
	gameObjs.push_back(obj);
}
*/