#include "stdafx.h"
#include "sound.h"
#include <windows.h>
#include <string>

using namespace std;

string path = "sound/";

Sound::Sound(){
	/* Cannot call play in the constructor !!! */
	// game view explosion sound
	string tmp = path + "explosion.wav";
	if (!explosionBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	explosionSound.setBuffer(explosionBuffer);
	explosionSound.setPosition(1,0,-5);// create a 3d spatioal sound
	//explosionSound.play();

	// build view selection sound
	tmp = path + "select.wav";
	if (!selectBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	selectSound.setBuffer(selectBuffer);
	selectSound.setLoop(true); 
	// need to play and then pause it
	selectSound.play();
	selectSound.pause();

	// game background music
	// music doesn't preload the data
	if (!music.openFromFile("Payback.wav"))
		cout << "load music error " << endl;
	music.setVolume(70); // lower the sound of the background music

}


Sound::~Sound(){

}


// This function is used to play music
void Sound::playMusic(){
	// for the first time displayCallback calls the playMusic
	if (music.getStatus() != sf::Sound::Playing)
		music.play();
	/*
	if (music.getStatus() == sf::Sound::Playing){
		cout << "Playing music " << endl;
		music.pause();
		music.play();
	}*/
}


// This function is used to play sound, don't need to be play continued
void Sound::playExplosion(){
	if (explosionSound.getStatus() == sf::Sound::Paused){
		cout << "Playing " << endl;
		explosionSound.play();
		explosionSound.pause();
	}
}

// This function is used to play gui menu selection
void Sound::playSelect(){
	cout << "Enter play select " << endl;
	if (selectSound.getStatus() == sf::Sound::Paused){
		cout << "Play Select " << endl;
		selectSound.play();
		Sleep(100); // sleep for 0.1 secs and then pause
		selectSound.pause();
	}
}