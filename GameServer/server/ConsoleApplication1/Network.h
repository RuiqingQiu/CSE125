
/* Network.h */
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "ServerNetwork.h"
#include "NetworkData.h"
#include "Robot.h"
#include "GOBox.h"
#include "GOCapsule.h"
#include "GOCone.h"
#include "GOCylinder.h"
#include "GOPlane.h"
#include "GERobotDeath.h"
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
	void receiveFromClients(std::vector<ObjectEvents*>*);
	void sendActionPackets(vector<GameObj*> * gameObjs, vector<GameEvents*>*);
	void convertObjectEvents(CPacket packet, std::vector<ObjectEvents*>* eventList);
	string convertEventData(std::vector<GameEvents*>*);
	void sendInitBuild(int,int);
	void sendBuildRequest(int);
};
#endif

