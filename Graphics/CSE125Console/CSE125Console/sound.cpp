#include "stdafx.h"
#include "sound.h"

using namespace std;

Sound::Sound(){
	// The sound created here will play for the whole game
	if (!buffer.loadFromFile("Payback.wav"))
		cout << "ERROR!" << endl;
	// Create a sound instance and play it
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true); // the music will loop itself when ends
	

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
	
	if (sound.getStatus() == sf::Sound::Playing){
		cout << "Playing " << endl;
		// do a little trick here, pause the sound and play again
		sound.pause();
		sound.play();
	}
}