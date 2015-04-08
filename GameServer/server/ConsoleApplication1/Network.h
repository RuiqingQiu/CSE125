
/* Network.h */
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "ServerNetwork.h"
#include "NetworkData.h"
#include "definition.h"
#include "Events.h"
#include <string>
class Network {
private:
	// IDs for the clients connecting for table in ServerNetwork 
	int client_id;

	// The ServerNetwork object 
	ServerNetwork* network;


	// data buffer
	char network_data[MAX_PACKET_SIZE];
public:
	Network();
	~Network();
	void sendClientConfirmationPacket(const char* clientName, int client_ID);
	int waitForConnections();
	string convertData(vector<GameObj*> * gameObjs);
	void receiveFromClients(std::vector<Events*>*);
	void sendActionPackets(vector<GameObj*> * gameObjs);
	void convertEvents(CPacket packet, std::vector<Events*>* eventList);
};
#endif

