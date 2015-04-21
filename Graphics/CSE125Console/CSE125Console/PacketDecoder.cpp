#include "stdafx.h"
#include "PacketDecoder.h"
#define RAD_TO_DEGREE_MULT 57.2957795


PacketDecoder::PacketDecoder()
{
}


PacketDecoder::~PacketDecoder()
{
}

//Helper function for split strings
unsigned int split1(const std::string &txt, std::vector<std::string> &strs, char ch)
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

vector<PlayerInfo*> PacketDecoder::decodePacket(string data)
{
	vector<PlayerInfo*> ret;
	std::vector<std::string> v;
	split1(data, v, ' ');
	/*
	for (int i = 0; i < v.size(); i++){
	cout << v[i] << endl;
	}*/
	//1 + 3 + 16
	for (int i = 0; i < v.size() - 1; i += 8){
		PlayerInfo* p = new PlayerInfo();
		p->id = stoi(v[i]);
		p->x = stof(v[i + 1]);
		p->y = stof(v[i + 2]);
		p->z = stof(v[i + 3]);
		p->rx = stof(v[i + 4])*RAD_TO_DEGREE_MULT;
		p->ry = stof(v[i + 5])*RAD_TO_DEGREE_MULT;
		p->rz = stof(v[i + 6])*RAD_TO_DEGREE_MULT;
		p->type = stoi(v[i + 7]);
		//Check if this is something belong to that player
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
		ret.push_back(p);
	}
	return ret;
}