#ifndef PLAYING_H
#define PLAYING_H



#include "GameState.h"
#include "../fmod//fmod.hpp"


class SimpleGameObject;
class Timer;


class Playing : public GameState
{
public:

	Playing();
	virtual ~Playing();

	GameState * Update();

private:
	FMOD::Channel * soundChannel;

	void SetScoreIconLocations();
	void Update_And_Draw_Scoreboard();

	SimpleGameObject * clock;
	Timer * timer;



};

#endif
