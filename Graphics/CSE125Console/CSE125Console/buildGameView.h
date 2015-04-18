#pragma once

#include "GameView.h"
#include "robot.h"


class buildGameView : public GameView {
public:
	buildGameView();
	~buildGameView();

	void VOnRender();
	void VUpdate();

	robot * robo;
};

