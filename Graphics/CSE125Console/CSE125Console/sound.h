#include "stdafx.h"
#include <SFML/Audio.hpp>  // used SFML sound
#include <iostream>

// This class is used to display sound in the game
class Sound{

public:
	Sound();
	~Sound();

	void playSound(); // play the sound 
	void playMusic();

private:	
	//Init server info here later
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	sf::Sound sound;// lightweight obeject that plays loaded audio data from a sound buffer
	sf::Music music;// stream the data on the fly from the source file, play music that lasts several minites


};