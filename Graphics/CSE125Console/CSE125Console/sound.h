#include "stdafx.h"
#include <SFML/Audio.hpp>  // used SFML sound
#include <iostream>

#ifndef SOUND_H_
#define SOUND_H_

// This class is used to display sound in the game
class Sound{

public:
	Sound();
	~Sound();

	void playExplosion(float,float,float); // play the sound 
	void playMusic();
	void playSelect(); // play menu selection sound
	void playGun(float,float,float); // play gun shot sound

private:
	//Init server info here later
	// Load a sound buffer from a wav file
	sf::SoundBuffer hammerBuffer;
	sf::SoundBuffer explosionBuffer;
	sf::SoundBuffer selectBuffer;
	sf::SoundBuffer gunBuffer;

	sf::Sound explosionSound;
	sf::Sound hammerSound;// lightweight obeject that plays loaded audio data from a sound buffer
	sf::Sound selectSound;
	sf::Sound gunSound;

	// music will play for the whole game, all other effects are sound
	sf::Music music;// stream the data on the fly from the source file, play music that lasts several minites
};
#endif