#pragma once
class GameInputInterface
{
public:
	GameInputInterface();
	~GameInputInterface();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);
};

