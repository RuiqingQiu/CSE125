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
	std::cout << "Sending Confirmation Packet" << endl;
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
	memset(packet.data, 0, sizeof(packet.data));
	memcpy(packet.data, packetInfoStr.c_str(), packetInfoStr.length());

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



void Network::receiveFromClients(std::vector<ObjectEvents*>* eventList){
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
			convertObjectEvents(packet, eventList);
		}
	}



}

void Network::sendActionPackets(vector<GameObj*> * gameObjs, vector<GameEvents*>* ge){

	//cout << "send Action" << endl;
	// send action packet
	if (gameObjs == nullptr)
	{
		std::cout << "null ptr\n" << endl;
	}

	const unsigned int packet_size = sizeof(SPacket);
	char packet_data[packet_size];

	//GameObj* obj = new GameObj(1, -1, -5);
	//GameObj* obj2 = new GameObj(1, -2, -5);


	SPacket packet;
	//packet.data[0] = '1';

	//string des = "1 1 1 0";

	string des = convertData(gameObjs);
	//string des;
	des += convertEventData(ge);
	//cout << "convertEvent " << des.c_str() << endl;
	//cout << "*********Sending SPacket: " << des << endl;
	memset(packet.data, 0, sizeof(packet.data));
	//char* str = new char[sizeof(des) + 1];
	//std::strcpy(str, des.c_str());
	//cout << "packet size is : "<< sizeof(des) << endl;
	memcpy(packet.data, des.c_str(), des.length());
	//cout << "size of des: " << sizeof(des) << endl;
	//cout << "des.cstr: " << des.c_str() << endl;
	cout << "packet.data: " << packet.data << endl;
	//cout << "AFTER MEM COPY" << endl;
	packet.packet_type = GAME_STATE;

	packet.serialize(packet_data);
	//cout << "BERFORE SEND TO ALL" << endl;
	//cout << packet.packet_type << endl;
	network->sendToAll(packet_data, packet_size);

	//cout << "AFTER SEND TO ALL" << endl;

}



void Network::convertObjectEvents(CPacket packet, std::vector<ObjectEvents*>* eventList){

	//cout << "packet type : " << packet.packet_type << endl;
	switch (packet.packet_type) {
	case INIT_CONNECTION: {
							  ObjectEvents * e = new ObjectEvents(INIT_CONNECTION);
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
						cout << "Move Left" << endl;
						ObjectEvents * e = new ObjectEvents(MOVE_LEFT);
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
						//cout << packet.data << endl;
						//cout << "recieved string "<< packetInfoStr << endl;
						int cid = stoi(packetInfoStr);
						//cout << "recived cid = " << cid << endl;
						e->setCid(cid);
						eventList->push_back(e);
						break;
	}
	case MOVE_RIGHT: {
						 cout << "Move Right" << endl;
						 ObjectEvents * e = new ObjectEvents(MOVE_RIGHT);
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
							cout << "Move Backward" << endl;
							ObjectEvents * e = new ObjectEvents(MOVE_BACKWARD);
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
						   cout << "Move Forward" << endl;
						   ObjectEvents * e = new ObjectEvents(MOVE_FORWARD);
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
					  ObjectEvents * e = new ObjectEvents(MOVE_UP);
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
						ObjectEvents * e = new ObjectEvents(MOVE_DOWN);
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
	case SHOOT:{
				   ObjectEvents * e = new ObjectEvents(SHOOT);
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
	case BUILD_ROBOT: {
						  ObjectEvents * e = new ObjectEvents(BUILD_ROBOT);
						  
							  string parseData = string(packet.data);
						  
							  vector<string> splitByObject = vector<string>();
						  splitByObject.push_back("");
						  
							  for (int i = 0; i < parseData.length(); i++) {
							  				   //split by newline, each newline
								  if (parseData[i] != '\n')
								   splitByObject[splitByObject.size() - 1] += parseData[i];
					   else
					   {
						   splitByObject.push_back("");
					   }
								  //pop last empty string
								  splitByObject.pop_back();
								  unsigned int cid;
									  for (int i = 0; i < splitByObject.size(); i++) {
									  string objectInfo = splitByObject[i];
									  					   //split by space to get the information for each object
									  size_t pos = 0;
									  string token;
									  					   /*
														   					   while ((pos = objectInfo.find(" ")) != string::npos) {
														   					   token = objectInfo.substr(0, pos);
														   					   std::cout << token << std::endl;
														   					   objectInfo.erase(0, pos  + 1);
														   					   }
														   					   */
														   
														   					   //CID
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  cid = stoul(token);
									  objectInfo.erase(0, pos  + 1);
									  					   //Object ID
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  unsigned int objId = stoul(token);
									  objectInfo.erase(0, pos  + 1);
									  
										  					   //position
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									 // std::cout << token << std::endl;
									  double xPos = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double yPos = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double zPos = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  
										  					   //rotation
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									 // std::cout << token << std::endl;
									  double xRot = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double yRot = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double zRot = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  
										  					   //block type
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									 // std::cout << token << std::endl;
									  double block_type = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  
										  					   //contraints
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double below = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									 // std::cout << token << std::endl;
									  double left = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double right = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double front = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double back = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  
										  					   //stats
										  pos = objectInfo.find(" ");
									  token = objectInfo.substr(0, pos);
									  //std::cout << token << std::endl;
									  double health = stold(token);
									  objectInfo.erase(0, pos  + 1);
									  
									  GameObj* object;
									  btQuaternion rotations = btQuaternion();
									  rotations.setEuler(yRot, xRot, zRot);


									  //(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double width, double height, double depth)
								     if (objId == 0) {

										object = new Robot((int)cid, "Player");
										  
										object->setX(xPos);
										object->setY(yPos);
										object->setZ(zPos);
										object->setqX(rotations.getX());
										object->setqY(rotations.getY());
										object->setqZ(rotations.getZ());
										object->setqW(rotations.getW());
										object->setType(BOX);
										((Robot*)object)->setWidth(3);
										((Robot*)object)->setHeight(1);
										((Robot*)object)->setDepth(3);
									  }
									else
									{
										object = new GOBox(xPos, yPos, zPos, rotations.getX(), rotations.getY(), rotations.getZ(), rotations.getW(), 10, 1, 1, 1);
										object->setIsRobot(0);
										object->setCollisionType(C_ROBOT_PARTS);
									}
									  
										
									  object->setBlockType(block_type);
									  object->setBuildID(objId);
									  object->setBelowID(below);
									  object->setLeftID(left);
									  object->setRightID(right);
									  object->setFrontID(front);
									  object->setBackID(back);
									  object->setHealth(health);
									  e->roboBuild.push_back(object);
									  
								  }
								  splitByObject.clear();
								  e->setCid(cid);
									  eventList->push_back(e);
								  break;
				   }
	}
	default:{
				printf("error in packet types\n");
				break;
	}

	}
}


static string temp;
static string temp1;
string Network::convertData(vector<GameObj*> * gameObjs){
	temp = "";
	//cout <<"GAME OBJ SIZE IS : "<< gameObjs->size() << endl;\

	if (gameObjs == nullptr)
	{
		std::cout << "NULL" << endl;
		return temp;
	}

	for (vector<GameObj*>::iterator i = gameObjs->begin();
		i != gameObjs->end(); ++i)
	{
		if ((*i) == nullptr)
		{
			std::cout << "NULL" << endl;
			break;
		}

		temp += to_string((*i)->getId());
		temp += ' ';
		temp += to_string((*i)->getX());
		temp += ' ';
		temp += to_string((*i)->getY());
		temp += ' ';
		temp += to_string((*i)->getZ());
		temp += ' ';
		btTransform trans;
		if ((*i)->getIsRobot()){

			trans = ((Robot*)(*i))->getVehicle()->getChassisWorldTransform();
			//float mat[16];
			//trans.getOpenGLMatrix(mat);
			//int j;
			//for (j = 0; j < 16; j++)
			//{
			//	temp += to_string(mat[j]);
			//	temp += ' ';
			//}
			btScalar yaw = 0, pitch = 0, roll = 0;

			trans.getBasis().getEulerZYX(yaw, pitch, roll);
			//cout << "yaw : " << yaw << endl;
			//cout << "pitch : " << pitch << endl;
			//cout << "roll : " << roll << endl;
			temp += to_string((float)roll);
			temp += ' ';
			temp += to_string((float)pitch);
			temp += ' ';
			temp += to_string((float)yaw);
			temp += ' ';
		}
		else if ((*i)->getType() == PLANE)
		{
			temp += "0 0 0 ";
			//temp += to_string((float)((GOPlane*)(*i))->getXNorm());
			//temp += ' ';
			//temp += to_string((float)((GOPlane*)(*i))->getYNorm());
			//temp += ' ';
			//temp += to_string((float)((GOPlane*)(*i))->getZNorm());
			//temp += ' ';
		}
		else
		{
			(*i)->getRigidBody()->getMotionState()->getWorldTransform(trans);
			btScalar yaw = 0, pitch = 0, roll = 0;

			trans.getBasis().getEulerZYX(yaw, pitch, roll);
			//cout << "yaw : " << yaw << endl;
			//cout << "pitch : " << pitch << endl;
			//cout << "roll : " << roll << endl;
			temp += to_string((float)roll);
			temp += ' ';
			temp += to_string((float)pitch);
			temp += ' ';
			temp += to_string((float)yaw);
			temp += ' ';
		}

		temp += to_string((*i)->getBlockType());
		//std::cout << to_string((*i)->getBlockType()) << endl;
		temp += ' ';
		/*
		temp += to_string((*i)->getType());
		temp += ' ';*/
		//int type = (*i)->getBlockType();
		/*switch (type)
		{
			case BOX:
			{
				temp += to_string(((GOBox*)(*i))->getWidth());
				temp += ' ';
				temp += to_string(((GOBox*)(*i))->getHeight());
				temp += ' ';
				temp += to_string(((GOBox*)(*i))->getDepth());
				break;
			}
			case CAPSULE:
			{
				temp += to_string(((GOCapsule*)(*i))->getRadius());
				temp += ' ';
				temp += to_string(((GOCapsule*)(*i))->getHeight());
				break;
			}
			case CONE:
			{
				temp += to_string(((GOCone*)(*i))->getRadius());
				temp += ' ';
				temp += to_string(((GOCone*)(*i))->getHeight());
				break;
			}
			case CYLINDER:
			{
				temp += to_string(((GOCylinder*)(*i))->getRadius());
				temp += ' ';
				temp += to_string(((GOCylinder*)(*i))->getHeight());
				break;
			}
			case PLANE:
			{
				temp += to_string(((GOPlane*)(*i))->getXNorm());
				temp += ' ';
				temp += to_string(((GOPlane*)(*i))->getYNorm());
				temp += ' ';
				temp += to_string(((GOPlane*)(*i))->getZNorm());
				temp += ' ';
				temp += to_string(((GOPlane*)(*i))->getPlaneConst());
				break;
			}
		}*/
		//temp += '\n';


		if ((*i)->getIsRobot()){
				int k;
				for (k = 0; k < 4; k++){
					btTransform tran0 = ((Robot*)(*i))->getVehicle()->getWheelInfo(k).m_worldTransform;
				
					temp += to_string((*i)->getId()*5 + k + 100000);
					temp += ' ';
					temp += to_string(tran0.getOrigin().getX());
					temp += ' ';
					temp += to_string(tran0.getOrigin().getY());
					temp += ' ';
					temp += to_string(tran0.getOrigin().getZ());
					temp += ' ';

					btScalar yaw0 = 0, pitch0 = 0, roll0 = 0;

					tran0.getBasis().getEulerZYX(yaw0, pitch0, roll0);
					if (k == 3)
					{
						temp += to_string((float)180);
						temp += ' ';
						temp += to_string((float)pitch0);
						temp += ' ';
						temp += to_string((float)180);
						temp += ' ';
						temp += to_string(TIRE);
						temp += ' ';
					}
					else
					{

						
						//cout << "yaw : " << yaw << endl;
						//cout << "pitch : " << pitch << endl;
						//cout << "roll : " << roll << endl;
						temp += to_string((float)roll0);
						temp += ' ';
						temp += to_string((float)pitch0);
						temp += ' ';
						temp += to_string((float)yaw0);
						temp += ' ';
						temp += to_string(WOODENWHEEL);
						temp += ' ';
					}
				}
			}
	}
	//temp += "\0";
	//cout << temp << endl;
	//cout << "PASS THE FORLOOP and the temp is: "<< temp << endl;\

	return temp;
}



string Network::convertEventData(std::vector<GameEvents*>* ge)
{
	std::vector<GameEvents*>::iterator it;
	if (ge->empty())
	{
		temp1 = "-1~\0";
		return temp1;
	}

	temp1 = "|";
	for (it = ge->begin(); it != ge->end(); it++)
	{
		(*it)->to_string(temp1);
		temp1 += "~";
	}
	temp1 += "-1~\0";
	return temp1;
}