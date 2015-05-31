#include "stdafx.h"
#include "sound.h"
#include <windows.h>
#include <string>

using namespace std;

string path = "sound/";

Sound::Sound(){
	/* Cannot call play in the constructor !!! */
	// build view selection sound
	string tmp = path + "select.wav";
	if (!selectBuffer.loadFromFile(tmp))
		cout << "ERROR in loading select sound effect " << endl;
	selectSound.setBuffer(selectBuffer);
	selectSound.setLoop(true);
	// need to play and then pause it
	selectSound.play();
	selectSound.pause();

	// game view explosion sound
	tmp = path + "explosion.wav";
	if (!explosionBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	explosionSound.setBuffer(explosionBuffer);
	gunSound.play();
	gunSound.stop();

	// game view gun shot sound
	tmp = path + "gun.wav";
	if (!gunBuffer.loadFromFile(tmp))
		cout << "ERROR in loading gun sound effect " << endl;
	gunSound.setBuffer(gunBuffer);
	gunSound.play();
	gunSound.stop();

	// build view selection sound
	tmp = path + "select.wav";
	if (!selectBuffer.loadFromFile(tmp))
		cout << "ERROR in loading explosion sound effect " << endl;
	selectSound.setBuffer(selectBuffer);
	selectSound.setLoop(true);
	// need to play and then pause it
	selectSound.play();
	selectSound.pause();

	// loading view sound
	tmp = path + "loading.wav";
	if (!loadingBuffer.loadFromFile(tmp))
		cout << "ERROR in loading loading sound effect " << endl;
	loadingSound.setBuffer(loadingBuffer);
	loadingSound.setLoop(true);
	// need to play and then pause it
	loadingSound.play();
	loadingSound.stop();

	// this will be our game entry sound
	tmp = path + "opening.wav";
	if (!openingBuffer.loadFromFile(tmp))
		cout << "ERROR in loading opening sound effect " << endl;
	openingSound.setBuffer(openingBuffer);
	openingSound.setLoop(true);
	// need to play and then pause it
	openingSound.play();
	openingSound.stop();

	// ending sound
	tmp = path + "ending.wav";
	if (!endingBuffer.loadFromFile(tmp))
		cout << "ERROR in loading ending sound effect " << endl;
	endingSound.setBuffer(endingBuffer);
	endingSound.setLoop(true);
	// need to play and then pause it
	endingSound.play();
	endingSound.stop();

	// game background music
	// music doesn't preload the data
	if (!music.openFromFile("Payback.wav"))
		cout << "load music error " << endl;
	music.setVolume(70); // lower the sound of the background music

	// build view background music
	tmp = path + "buildViewBackground.wav";
	if (!buildViewBackground.openFromFile(tmp))
		cout << "load music error " << endl;// lower the sound of the background music
	buildViewBackground.setLoop(true);
	buildViewBackground.setVolume(70);
}


Sound::~Sound(){

}


// This function is used to play music
void Sound::playMusic(){
	// for the first time displayCallback calls the playMusic
	if (music.getStatus() != sf::Sound::Playing){
		music.play();
		buildViewBackground.stop();
		loadingSound.stop();
		openingSound.stop();
	}
	// without this part still working, so comment out for now
	/*
	if (music.getStatus() == sf::Sound::Playing){
	cout << "Playing music " << endl;
	music.pause();
	music.play();
	}*/
}

// this function is to play build view background music
void Sound::playBuildViewBackground(){
	if (buildViewBackground.getStatus() != sf::Sound::Playing){
		buildViewBackground.play();
		openingSound.stop();
		loadingSound.stop();
		music.stop();
	}
}

// This function is used to play sound, don't need to be play continued
// need user location to play 3d sound
void Sound::playExplosion(float x, float y,float z){
	// for the first time
	if (explosionSound.getStatus() == sf::Sound::Stopped){
		//cout << "Playing explosion sound " << endl;
		explosionSound.setPosition(x, y, z);
		explosionSound.play();
	}
	// cannot do sleep for gun sound effect
	if (explosionSound.getStatus() == sf::Sound::Playing){
		//cout << "Play explosion sound " << endl;
		explosionSound.stop();
		explosionSound.setPosition(x, y, z);
		explosionSound.play();
	}
 }


// This function is used to play gui menu selection
void Sound::playSelect(){
	//cout << "Enter play select " << endl;
	if (selectSound.getStatus() == sf::Sound::Paused){
		cout << "Play Select " << endl;
		selectSound.play();
		Sleep(100); // sleep for 0.1 secs and then pause
		selectSound.pause();
	}
}

// This function is used to play gun shot sound
void Sound::playGun(float x, float y, float z){
	cout << "Enter play gun shot effect " << endl;
	// for the first time
	if (gunSound.getStatus() == sf::Sound::Stopped){
		gunSound.play();
	}

	// cannot do sleep for gun sound effect
	if (gunSound.getStatus() == sf::Sound::Playing){
		cout << "Play gun " << endl;
		gunSound.setPosition(x, y, z);
		gunSound.stop();
		gunSound.play();
	}
}

// this function is to play the loading view sound
void Sound::playLoading(){
	//cout << "play loading sound " << endl;
	if (loadingSound.getStatus() == sf::Sound::Stopped){
		music.pause();
		openingSound.stop();
		loadingSound.play();
	}
}

// this function is to play the loading view sound
void Sound::playOpening(){
	//cout << "play opening sound " << endl;
	if (openingSound.getStatus() == sf::Sound::Stopped){
		openingSound.play();
	}
}


void Sound::playEnding(){
	cout << "play ending sound " << endl;
	if (endingSound.getStatus() == sf::Sound::Stopped){
		music.pause();
		openingSound.stop();
		loadingSound.stop();
		endingSound.play();
	}
}
