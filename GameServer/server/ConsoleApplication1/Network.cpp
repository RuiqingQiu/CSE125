#include "Network.h"


Network::Network()
{
	// id's to assign clients for our table
	client_id = 0;

	// set up the server network to listen 
	network = new ServerNetwork();
}


Network::~Network()
{
	delete network;
}


void Network::sendClientConfirmationPacket(const char* clientName, int client_ID){
	cout << "Sending Confirmation Packet" << endl;
	const unsigned int packet_size = sizeof(SPacket);
	char packet_data[packet_size];

	SPacket packet;
	packet.packet_type = CONFIRM_CONNECTION;
	string packetInfoStr = "";
	int i;
	for (i = 0;; i++)
	{
		if (clientName[i] != '\0')
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




int Network::waitForConnections(){
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		client_id++;
		return client_id-1;
	}
	return -1;
}



void Network::receiveFromClients(std::vector<Events*>* eventList){
	CPacket packet;
	//cout << gameObjs.size() << endl;

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
			convertEvents(packet, eventList);
		}
	}



}

void Network::sendActionPackets(vector<GameObj*> * gameObjs){

	//cout << "send Action" << endl;
	// send action packet
	if (gameObjs == nullptr)
	{
		cout << "null ptr\n" << endl;
	}

	const unsigned int packet_size = sizeof(SPacket);
	char packet_data[packet_size];

	//GameObj* obj = new GameObj(1, -1, -5);
	//GameObj* obj2 = new GameObj(1, -2, -5);


	SPacket packet;
	//packet.data[0] = '1';

	//string des = "1 1 1 0";

	string des = convertData(gameObjs);

	memset(packet.data, 0, sizeof(packet.data));

	//cout << "packet size is : "<< sizeof(des) << endl;
	memcpy(packet.data, des.c_str(), sizeof(des));
	
	//cout << "AFTER MEM COPY" << endl;
	packet.packet_type = GAME_STATE;

	packet.serialize(packet_data);
	//cout << "BERFORE SEND TO ALL" << endl;

	network->sendToAll(packet_data, packet_size);

	//cout << "AFTER SEND TO ALL" << endl;

}



void Network::convertEvents(CPacket packet, std::vector<Events*>* eventList){

	cout << "packet type : " << packet.packet_type << endl;
	switch (packet.packet_type) {
		case INIT_CONNECTION: {
								  Events * e = new Events(INIT_CONNECTION);
								  string packetInfoStr = "";
								  int i;
								  for (i = 0;; i++)
								  {
									  if (packet.data[i] != '\n')
										  packetInfoStr += packet.data[i];
									  else
									  {
										  break;
									  }
								  }
								  string name = packetInfoStr;
								  //cout << name << endl;
								  e->setName(packetInfoStr);
								  //cout << e->getName() << endl;
								  eventList->push_back(e);
							      break;
		}
		case MOVE_LEFT: {
						Events * e = new Events(MOVE_LEFT);
						string packetInfoStr = "";
						int i;
						for (i = 0;; i++)
						{
							if (packet.data[i] != '\n')
								packetInfoStr += packet.data[i];
							else
							{
								break;
							}
						}
						cout << packet.data << endl;
						cout << "recieved string "<< packetInfoStr << endl;
						int cid = stoi(packetInfoStr);
						cout << "recived cid = " << cid << endl;
						e->setCid(cid);
						eventList->push_back(e);
						break;
		}
		case MOVE_RIGHT: {
							 Events * e = new Events(MOVE_RIGHT);
							 string packetInfoStr = "";
							 int i;
							 for (i = 0;; i++)
							 {
								 if (packet.data[i] != '\n')
									 packetInfoStr += packet.data[i];
								 else
								 {
									 break;
								 }
							 }
							 unsigned int cid = stoul(packetInfoStr);
							 e->setCid(cid);
							 eventList->push_back(e);
							 break;
	
		}
		case MOVE_BACKWARD: {
								Events * e = new Events(MOVE_BACKWARD);
								string packetInfoStr = "";
								int i;
								for (i = 0;; i++)
								{
									if (packet.data[i] != '\n')
										packetInfoStr += packet.data[i];
									else
									{
										break;
									}
								}
								unsigned int cid = stoul(packetInfoStr);
								e->setCid(cid);
								eventList->push_back(e);
								break;

		}
		case MOVE_FORWARD: {
							   Events * e = new Events(MOVE_FORWARD);
							   string packetInfoStr = "";
							   int i;
							   for (i = 0;; i++)
							   {
								   if (packet.data[i] != '\n')
									   packetInfoStr += packet.data[i];
								   else
								   {
									   break;
								   }
							   }
							   unsigned int cid = stoul(packetInfoStr);
							   e->setCid(cid);
							   eventList->push_back(e);
							   break;


						   break;
		}
		case MOVE_UP: {
						  Events * e = new Events(MOVE_UP);
						  string packetInfoStr = "";
						  int i;
						  for (i = 0;; i++)
						  {
							  if (packet.data[i] != '\n')
								  packetInfoStr += packet.data[i];
							  else
							  {
								  break;
							  }
						  }
						  unsigned int cid = stoul(packetInfoStr);
						  e->setCid(cid);
						  eventList->push_back(e);
						  break;

		}

		case MOVE_DOWN: {
							Events * e = new Events(MOVE_DOWN);
							string packetInfoStr = "";
							int i;
							for (i = 0;; i++)
							{
								if (packet.data[i] != '\n')
									packetInfoStr += packet.data[i];
								else
								{
									break;
								}
							}
							unsigned int cid = stoul(packetInfoStr);
							e->setCid(cid);
							eventList->push_back(e);
							break;
		}
		default:{
					printf("error in packet types 222222\n");
					break;
		}
	}
}


static string temp;

string Network::convertData(vector<GameObj*> * gameObjs){
	temp = "";
	//cout <<"GAME OBJ SIZE IS : "<< gameObjs->size() << endl;\

	if (gameObjs == nullptr)
	{
		cout << "NULL" << endl;
		return temp;
	}

	for (vector<GameObj*>::iterator i = gameObjs->begin();
		i != gameObjs->end(); ++i)
	{
		if ((*i) == nullptr)
		{
			cout << "NULL" << endl;
			break;
		}

		temp += to_string((*i)->getId());
		temp += ' ';
		temp += to_string((*i)->getX());
		temp += ' ';
		temp += to_string((*i)->getY());
		temp += ' ';
		temp += to_string((*i)->getZ());
		temp += '\n';
	}
	
	temp += "\0";
	//cout << "PASS THE FORLOOP and the temp is: "<< temp << endl;
	return temp;
}