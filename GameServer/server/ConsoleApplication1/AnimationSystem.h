#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class AnimationSystem
{
public:
	AnimationSystem();
	~AnimationSystem();
	void InitAnimationSystemWithStartingTime(float globalTimerStart);
	void InitAnimationSystemWithAnimationFile(std::string filename);

	void StepAnimationSystem(float deltaTime);
	bool IsSystemInitialized = false;
	bool IsAnimationFileParsed = false;
	float globalTimer = 0;
	std::vector<AnimationChanel*> chanels;
};

class AnimationChanel
{
public:
	AnimationChanel();
	~AnimationChanel();
	int ObjectId = -1;
	std::vector<std::pair<float, float>> AnimationTimePeriod;
	std::vector<std::pair<float, Vector3>> KeyFrames;
	bool GetUpdatePacket(float seconds, std::pair<int, Vector3> &output);
};

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator+(const Vector3&); //overload operator '+' for addition
	Vector3 operator-(const Vector3&); //overload operator '-' for subtraction
	Vector3 operator*(float); //overload operator '+' for addition
	~Vector3();
	float x = 0;
	float y = 0;
	float z = 0;
};

