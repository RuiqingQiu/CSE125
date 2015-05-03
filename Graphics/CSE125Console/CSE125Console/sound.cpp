#include "stdafx.h"
#include "sound.h"
#include <string>

using namespace std;

string path = "sound/";

Sound::Sound(){
	/*
	// Sound effect for hammer
	if (!hammerBuffer.loadFromFile("Payback.wav"))
		cout << "ERROR!" << endl;
	// Create a sound instance and play it
	hammerSound.setBuffer(hammerBuffer);
	hammerSound.play();
	hammerSound.setLoop(true); // the music will loop itself when ends
	*/
	// This is for the explosion sound
	string tmp = path + "explosion.wav";
	if (!explosionBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	explosionSound.setBuffer(explosionBuffer);
	explosionSound.setPosition(1,0,-5);// create a 3d spatioal sound
	explosionSound.play();

	tmp = path + "select.wav";
	if (!selectBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	selectSound.setBuffer(selectBuffer);
	selectSound.play();

	// music doesn't preload the data
	if (!music.openFromFile("Payback.wav"))
		cout << "load music error " << endl;
	music.play();
}


Sound::~Sound(){

}


// This function is used to play music
void Sound::playMusic(){
	if (music.getStatus() == sf::Sound::Playing){
		cout << "Playing music " << endl;
		music.pause();
		music.play();
	}
}

// This function is used to play sound
void Sound::playSound(){
	if (explosionSound.getStatus() == sf::Sound::Playing){
		cout << "Playing " << endl;
		explosionSound.pause();
		explosionSound.play();
	}
}

void Sound::playSelect(){
	if (selectSound.getStatus() == sf::Sound::Playing){
		selectSound.pause();
		selectSound.play();
	}
}