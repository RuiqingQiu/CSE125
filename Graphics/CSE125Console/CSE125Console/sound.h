#include "stdafx.h"
#include <SFML/Audio.hpp>  // used SFML sound
#include <iostream>

// This class is used to display sound in the game
class Sound{

public:
	Sound();
	~Sound();

	void playSound(); // play the sound 

private:	
	//Init server info here later
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	sf::Sound sound;


};