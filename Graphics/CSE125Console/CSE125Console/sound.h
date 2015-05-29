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
	void playBuildViewBackground();// play build view background music
	void playLoading();
	void playOpening(); // game starts
	void playEnding(); // game ends

private:
	//Init server info here later
	// Load a sound buffer from a wav file
	sf::SoundBuffer hammerBuffer;
	sf::SoundBuffer explosionBuffer;
	sf::SoundBuffer selectBuffer;
	sf::SoundBuffer gunBuffer;
	sf::SoundBuffer loadingBuffer;
	sf::SoundBuffer openingBuffer; // for playing opening sound in mainmenu
	sf::SoundBuffer endingBuffer; // for ending sound 

	sf::Sound explosionSound;
	sf::Sound hammerSound;// lightweight obeject that plays loaded audio data from a sound buffer
	sf::Sound selectSound;
	sf::Sound gunSound;
	sf::Sound loadingSound; // this is for the main menu loading
	sf::Sound openingSound; // this is for main menu opening sound (game starts)
	sf::Sound endingSound; // ending sound 

	// music will play for the whole game, all other effects are sound
	sf::Music music;// stream the data on the fly from the source file, play music that lasts several minites
	sf::Music buildViewBackground; // background music for build view

};
#endif