#pragma once
class Weapon
{
private:
	int _type;
	double _damage;
	double _attackSpeed;
	double _mass;

	double _projectileSpeed;

public:
	Weapon(int, double, double, double);
	~Weapon();

	void setProjectileSpeed(double);

	int getType();
	double getDamage();
	double getAttackSpeed();
	double getProjectileSpeed();
	double getMass();
};

