#ifndef SOUND_H
#define SOUND_H



#include <ddraw.h>
#include <MMSystem.h>
#include <dsound.h>
#include <string>
#include "../fmod//fmod.hpp"

using namespace std;


class Sound
{

public:


 	static FMOD::Sound * explosion_sound;
 	static FMOD::Sound * drop_bomb_sound;
 	static FMOD::Sound * pickup_powerup_sound;
 	static FMOD::Sound * player_dies_sound;
	static FMOD::Sound * playing;
	static FMOD::Sound * pickingStuff;
	static FMOD::Sound * selectorMoved;
	static FMOD::Sound * selectionMade;
	static FMOD::Sound * opening;
	static FMOD::Sound * creditsWhoosh;
	static FMOD::Sound * gameStart;

	static FMOD::System * fmod_System;

	static void InitSounds();
	static FMOD::Sound * InitSound(const string & waveFileName, FMOD_MODE  mode = FMOD_DEFAULT );
	static FMOD::Channel * PlaySound(FMOD::Sound * aSound, float volumeLevel = 1.0f);
	static void StopSound(FMOD::Channel * aChannel );

};

#endif