#include "MSound.h"

#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/t3dlib3.h"


#include "dxutil.h"
//#include "AudioEngine.h"

#include <vector>

using namespace std;

#include "../fmod/fmod.hpp"
#include "../fmod/fmod_errors.h"


FMOD::Sound * Sound::explosion_sound = 0;
FMOD::Sound * Sound::drop_bomb_sound = 0;
FMOD::Sound * Sound::pickup_powerup_sound = 0;
FMOD::Sound * Sound::player_dies_sound = 0;
FMOD::Sound * Sound::playing = 0;
FMOD::Sound * Sound::pickingStuff = 0;
FMOD::Sound * Sound::selectorMoved = 0;
FMOD::Sound * Sound::selectionMade = 0;
FMOD::Sound * Sound::opening = 0;
FMOD::Sound * Sound::creditsWhoosh = 0;
FMOD::Sound * Sound::gameStart = 0;




	
FMOD::System * Sound::fmod_System = 0;



void ERRCHECK(	FMOD_RESULT & result)
{
	if (result != FMOD_OK)
	{

		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		char buffer[150];
		sprintf(buffer, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		OutputDebugString(buffer);
		exit(-1);
	}

}


void Sound::InitSounds()
{

	FMOD_RESULT result;


	result = FMOD::System_Create(&fmod_System);		// Create the main system object.
	if (result != FMOD_OK)
	{
		int x = 3;
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = fmod_System->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	explosion_sound = InitSound("waves/Explosion-From-Base.wav");
	drop_bomb_sound = InitSound("waves/BombDrop.mp3");
	pickup_powerup_sound = InitSound("waves/PickupPowerup.mp3");
	player_dies_sound = InitSound("waves/gameover04.wav");
	playing = InitSound("waves/PlayingA.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE);
	pickingStuff = InitSound("waves/PickingStuff.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE);
	selectorMoved = InitSound("waves/SelectorMoved.mp3");
	selectionMade = InitSound("waves/SelectionMade.mp3");
	opening = InitSound("waves/Opening.mp3");
	creditsWhoosh = InitSound("waves/airwhoosh15.wav");
	gameStart = InitSound("waves/TransitionToGameStart.mp3");


}




FMOD::Sound *  Sound::InitSound(const string & waveFileName,FMOD_MODE  mode )
{

	FMOD::Sound *sound;

	FMOD_RESULT result = fmod_System->createSound(waveFileName.c_str(), mode, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	ERRCHECK(result);
	return sound;

}


void Sound::StopSound(FMOD::Channel * aChannel )
{
	aChannel->stop();
}


FMOD::Channel * Sound::PlaySound(FMOD::Sound * aSound, float volumeLevel)
{
	FMOD::Channel *channel;

	bool paused = true;
 	FMOD_RESULT result = fmod_System->playSound(FMOD_CHANNEL_FREE, aSound, paused, &channel );
 	ERRCHECK(result);

	result = channel->setVolume(volumeLevel);		// Set the volume while it is paused.
	ERRCHECK(result);
	result = channel->setPaused(false);		// This is where the sound really starts.
	ERRCHECK(result);


	fmod_System->update();
	return channel;
}


// void Sound::StopSound(int soundId)
// {
// 	DSound_Stop_Sound(soundId );
// }


