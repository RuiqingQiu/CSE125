#include "GEUpdateHp.h"
#include <iostream>


GEUpdateHp::GEUpdateHp(int cid, int maxHp, int Hp)
:GameEvents(4)
{
	_cid = cid;
	_maxHp = maxHp;
	_Hp = Hp;
	//TODO: change int
}


GEUpdateHp::~GEUpdateHp()
{
}


void GEUpdateHp::to_string(std::string& s){

	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(_cid);
	s += " ";
	s += std::to_string(_maxHp);
	s += " ";
	s += std::to_string(_Hp);
	//std::cout << "to string:"<< s << "end"<< std::endl;
}
