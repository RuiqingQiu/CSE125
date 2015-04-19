#include "StdAfx.h"
#include "ClientGame.h"
#define RAD_TO_DEGREE_MULT 57.2957795
ClientGame::ClientGame(void)
{

    network = new ClientNetwork();

   
}

bool ClientGame::connectToServer(char* ipaddress)
{

	bool isConnectSuccess = network->connectToServer(ipaddress);

	if (!isConnectSuccess)
	{
		return false;
	}
	// send init packet
	const unsigned int packet_size = sizeof(CPacket);
	char packet_data[packet_size];

	CPacket packet;

	packet.packet_type = INIT_CONNECTION;
	string tmp = "Thomas\n\0";
	strncpy_s(packet.data, tmp.c_str(), sizeof(packet.data));
	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);

	return true;
}


ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(CPacket);
    char packet_data[packet_size];

    CPacket packet;
    packet.packet_type = 1;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

bool ClientGame::sendPacket(CPacket packet)
{
	printf(packet.data);
	const unsigned int packet_size = sizeof(CPacket);
	char packet_data[packet_size];

	packet.serialize(packet_data);

	printf("send %d\n", packet.packet_type);
	return NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}
//Helper function for split strings
unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

GameInfoPacket* ClientGame::update()
{
    GameInfoPacket* g = new GameInfoPacket();
    SPacket packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
		return nullptr;
    }
	//return network_data;
    int i = 0;
   
	while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(SPacket);

        switch (packet.packet_type) {

		case GAME_STATE:
				{
							 //printf("client received game state packet from server\n");
							 std::cout << packet.data << std::endl;
						    //cout << "game_state" << endl;
						    std::string result = std::string(packet.data);
							 if (result == ""){
								 return nullptr;
							 }
							 //Process the result
							 else{
								 std::vector<std::string> v;
								 split(result, v, ' ');
								 /*
								 for (int i = 0; i < v.size(); i++){
									 cout << v[i] << endl;
								 }*/
								 //1 + 3 + 16
								 for (int i = 0; i < v.size()-1; i += 7){
									 PlayerInfo* p = new PlayerInfo();
									 p->id = stof(v[i]);
									 p->x = stof(v[i+1]);
									 p->y = stof(v[i+2]);
									 p->z = stof(v[i+3]);
									 p->rx = stof(v[i + 4])*RAD_TO_DEGREE_MULT;
									 p->ry = stof(v[i + 5])*RAD_TO_DEGREE_MULT;
									 p->rz = stof(v[i + 6])*RAD_TO_DEGREE_MULT;
									 p->processed = false;
									 //p->print();
									 /*
									 for (int j = 0; j < 16; j++){
										 p->mat[j] = stof(v[i + 4 + j]);
										// printf("%f, ", p->mat[j]);
										 if (j % 4 == 0){
											 //printf("\n");
										 }
									 }*/
									 g->player_infos.push_back(p);
								 }
								 //std::cout << "pushing " << g->player_infos.size() << " on to the list" << std::endl;
								 g->packet_types = packet.packet_type;
							 }
							 //sendActionPackets();
							 return g;
							 break;
				}
		case CONFIRM_CONNECTION:
		{
								   cout << "fonfirm_packet" << endl;
			std::string result = std::string(packet.data);
			std::vector<std::string> v;
			split(result, v, '\n');
			std::cout << "from confirm connection" << std::endl;
			std::cout << packet.data << std::endl;
			g->packet_types = packet.packet_type;
			PlayerInfo* p = new PlayerInfo();
			std::cout << v[1] << std::endl;
			p->id = stoi(v[1]);
			g->player_infos.push_back(p);
			return g;
			break;

		}
		
		default:{

					printf("error in packet types : %i with length: %i\n", packet.packet_type, data_length);
					//std::cout << packet.data << std::endl;
					return nullptr;
					break;
		}
		}
    }
	return g;

	
}
