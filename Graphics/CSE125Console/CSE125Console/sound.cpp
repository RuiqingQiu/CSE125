#include "stdafx.h"
#include "sound.h"
#include <windows.h>
#include <string>

using namespace std;

string path = "sound/";

Sound::Sound(){
	// This is for the explosion sound
	string tmp = path + "explosion.wav";
	if (!explosionBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	explosionSound.setBuffer(explosionBuffer);
	explosionSound.setPosition(1,0,-5);// create a 3d spatioal sound
	//explosionSound.play();

	tmp = path + "select.wav";
	if (!selectBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	selectSound.setBuffer(selectBuffer);
	selectSound.setLoop(true); 

	// music doesn't preload the data
	if (!music.openFromFile("Payback.wav"))
		cout << "load music error " << endl;
	//music.play();
}


Sound::~Sound(){

}


// This function is used to play music
void Sound::playMusic(){
	if (music.getStatus() == sf::Sound::Paused){
		cout << "Playing music " << endl;
		music.play();
		music.pause();
	}
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
		//Sleep(100); // sleep for 0.1 secs and then pause
		//selectSound.pause();
	}
}