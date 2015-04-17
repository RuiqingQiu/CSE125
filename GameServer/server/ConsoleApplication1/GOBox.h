#pragma once
#include "GameObj.h"
class GOBox : public GameObj
{
private:
	double _width;
	double _height;
	double _depth;

public:

	GOBox(double, double, double, double, double, double, double, double, double, double, double);
	~GOBox();
	void setWidth(double);
	void setHeight(double);
	void setDepth(double);
	double getWidth();
	double getHeight();
	double getDepth();
	void createRigidBody() override;
};