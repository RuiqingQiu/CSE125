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



unsigned int ServerGame::waitForConnections()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		GameObj * clientOb = new GameObj();
		this->pushGameObj(*clientOb);
		clientPair.insert(std::pair<unsigned int, GameObj>(client_id, *clientOb));
		printf("client %d has been connected to the server\n", client_id);

		client_id++;
	}

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
		while (i < (int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(CPacket);

			switch (packet.packet_type) {

			case INIT_CONNECTION:

				printf("Server received INIT_CONNECTION packet from client with name: %s\n", packet.data);
				sendClientConfirmationPacket(packet.data, iter->first);
				break;
			}
		}
	}
	if (client_id >= 4) return 1;
	else return 0;
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
		while (i < (int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(CPacket);

			switch (packet.packet_type) {

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

	GameObj* obj = new GameObj(1, -1, -5);
	//GameObj* obj2 = new GameObj(1, -2, -5);


	SPacket packet;
	//packet.data[0] = '1';

	//char* des = "wrong";

	this->pushGameObj(*obj);
	string des = convertData();

	memcpy(packet.data, des.c_str(), sizeof(packet.data));

	packet.packet_type = 1;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

// convert gameobjs to jason file
string ServerGame::convertData(){
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

}

std::vector<GameObj> ServerGame::getGameObjs()
{
	return gameObjs;
}

void ServerGame::pushGameObj(GameObj obj)
{
	gameObjs.push_back(obj);
}


void ServerGame::sendClientConfirmationPacket(char* clientName, unsigned int client_ID)
{
	cout << "Sending Confirmation Packet" << endl;
	const unsigned int packet_size = sizeof(SPacket);
	char packet_data[packet_size];

	SPacket packet;
	packet.packet_type = CONFIRM_CONNECTION;
	string packetInfoStr = "";
	int i;
	for (i = 0;; i++)
	{
		if (clientName[i] != '\n')
			packetInfoStr += clientName[i];
		else
		{
			packetInfoStr += '\n';
			break;
		}
	}
	packetInfoStr += to_string(client_ID);
	packetInfoStr += '\n';
	memcpy(packet.data, packetInfoStr.c_str(), sizeof(packet.data));

	packet.serialize(packet_data);
	network->sendToOne(packet_data, packet_size, client_ID);
}




