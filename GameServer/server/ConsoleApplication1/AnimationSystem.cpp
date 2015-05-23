#include "AnimationSystem.h"
#include <time.h>
#include <limits>
std::vector<std::string> &animsplit(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> animsplit(const std::string &s, char delim) {
	std::vector<std::string> elems;
	animsplit(s, delim, elems);
	return elems;
}

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::InitAnimationSystemWithStartingTime(float globalTimerStart)
{
	globalTimer = globalTimerStart;
	IsSystemInitialized = true;
}

void AnimationSystem::StepAnimationSystem(float deltaTime)
{
	globalTimer += deltaTime;

	float TimeInSec = globalTimer / CLOCKS_PER_SEC;

	std::vector<std::pair<int, Vector3>> UpdatePackets;
	for each(AnimationChanel* chanel in chanels)
	{
		std::pair<int, Vector3> packet;
		bool b = chanel->GetUpdatePacket(TimeInSec, packet);
		if (b)
		{
			UpdatePackets.push_back(packet);
		}
	}

	//update the update packets here
	//...TODO
	for each (std::pair<int, Vector3> up in UpdatePackets)
	{
		printf("id : %i with pos %f %f %f\n", up.first, up.second.x, up.second.y, up.second.z);
	}
}

void AnimationSystem::InitAnimationSystemWithAnimationFile(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;
	AnimationChanel* chanel = nullptr;
	while (std::getline(infile, line))
	{
		//std::istringstream iss(line);
		//printf("%s\n", line.c_str());
		std::vector<std::string> tokens = animsplit(line.c_str(), ' ');
		//printf("%s\n", tokens[0].c_str());
		if (tokens.size() == 0)
		{
			//empty line
			continue;
		}
		else if (tokens[0].length()>2&&tokens[0][0] == '/'&&tokens[0][1] == '/')
		{
			//comment 
			continue;
		}
		else if (strcmp(tokens[0].c_str(),"ANIM") == 0)
		{
			//New Animation
			chanel = new AnimationChanel();
			float OBJID = stof(tokens[1]);
			chanel->ObjectId = OBJID;
		}
		else if (strcmp(tokens[0].c_str(), "FRAME") == 0)
		{
			//New frame
			if (chanel == nullptr){
				printf("Something wrong with animation file or parser");
				while (true)
				{
					//go infinit loop
				}
			}
			//add new frame
			float timeStart = stof(tokens[1]);
			float timeEnd = stof(tokens[2]);

			float sx = stof(tokens[3]);
			float sy = stof(tokens[4]);
			float sz = stof(tokens[5]);

			float ex = stof(tokens[6]);
			float ey = stof(tokens[7]);
			float ez = stof(tokens[8]);

			std::pair<float, Vector3> Startframe = std::make_pair(timeStart, Vector3(sx, sy, sz));
			std::pair<float, Vector3> Endframe = std::make_pair(timeEnd, Vector3(ex, ey, ez));

			chanel->KeyFrames.push_back(Startframe);
			chanel->KeyFrames.push_back(Endframe);

		}
		else if (strcmp(tokens[0].c_str(), "TIMEPERIOD")==0)
		{
			if (chanel == nullptr){
				printf("Something wrong with animation file or parser");
				while (true)
				{
					//go infinit loop
				}
			}

			float timeStart = stof(tokens[1]);
			float timeEnd = stof(tokens[2]);
			std::pair<float, float> period = std::make_pair(timeStart, timeEnd);

			chanel->AnimationTimePeriod.push_back(period);
		}
		else if (strcmp(tokens[0].c_str(), "PUSHANIM") == 0)
		{
			//printf("pushanimm\n");
			chanels.push_back(chanel);
			chanel = nullptr;
		}

	}
	IsAnimationFileParsed = true;
}

AnimationChanel::AnimationChanel()
{

}

AnimationChanel::~AnimationChanel()
{

}

bool AnimationChanel::GetUpdatePacket(float seconds, std::pair<int, Vector3> &output)
{
	bool IsInPeriod = false;
	for each (std::pair<float,float>  period in AnimationTimePeriod)
	{
		float s = period.first;
		float e = period.second;
		if (seconds > s&&seconds < e)
		{
			IsInPeriod = true;
		}
	}
	if (!IsInPeriod)
	{
		return false;
	}

	output.first = this->ObjectId;

	std::pair<float, Vector3> frame1 = std::make_pair(-INFINITY, Vector3(0,0,0));
	std::pair<float, Vector3> frame2 = std::make_pair(INFINITY, Vector3(0, 0, 0));

	for each (std::pair<float,Vector3> frame in KeyFrames)
	{
		if (frame.first > frame1.first && frame.first < seconds)
		{
			frame1 = frame;
		}
		if (frame.first < frame2.first && frame.first > seconds)
		{ 
			frame2 = frame;
		}
	}
	printf("in sec %f %f\n", frame1.first, frame2.first);

	//we get two frames, blend it
	float protion = (seconds - frame1.first) / (frame2.first - frame1.first);
	Vector3 NewPos = frame1.second + (frame2.second - frame1.second)*protion;
	output.second = NewPos;
	return true;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y; 
	z = _z;
}

Vector3::~Vector3()
{

}


Vector3 Vector3::operator+(const Vector3& v){
	//overload operator '+' for addition
	double x = this->x + v.x;
	double y = this->y + v.y;
	double z = this->z + v.z;
	return Vector3(x, y, z);
}
Vector3 Vector3::operator-(const Vector3& v){
	double x = this->x - v.x;
	double y = this->y - v.y;
	double z = this->z - v.z;
	return Vector3(x, y, z);
}//overload operator '-' for subtraction
Vector3 Vector3::operator*(float s){
	double x = this->x *s;
	double y = this->y *s;
	double z = this->z *s;
	return Vector3(x, y, z);
}//overload operator '-' for subtraction
