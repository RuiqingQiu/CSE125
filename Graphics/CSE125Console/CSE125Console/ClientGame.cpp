#include "StdAfx.h"
#include "ClientGame.h"

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
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

std::string ClientGame::update()
{
    SPacket packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
		return "";
    }
	//return network_data;
	
	
    int i = 0;
   
	while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(SPacket);

        switch (packet.packet_type) {

            case ACTION_EVENT:

                printf("client received action event packet from server\n");
				std::cout<< packet.data << std::endl;
                sendActionPackets();
				
                break;

            default:

                printf("error in packet types\n");

                break;
        }
    }
	return std::string(packet.data);

	
}
