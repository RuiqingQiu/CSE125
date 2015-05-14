#include "GECollisonHappen.h"


GECollisonHappen::GECollisonHappen(int collisiontype, double x, double y , double z)
:GameEvents(5)
{
	_collisiontype = collisiontype;
	_x = x;
	_y = y;
	_z = z;
}


GECollisonHappen::~GECollisonHappen()
{
}


void GECollisonHappen::to_string(std::string& s){
	s += std::to_string(this->getType());
	s += " ";

	s += std::to_string(this->_collisiontype);
	s += " ";

	s += std::to_string(this->_x);
	s += " ";

	s += std::to_string(this->_y);
	s += " ";

	s += std::to_string(this->_z);

	std::cout << "CH EVENT" << s << std::endl;

}