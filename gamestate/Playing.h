#ifndef PLAYING_H
#define PLAYING_H



#include "GameState.h"


class SimpleGameObject;
class Timer;


class Playing : public GameState
{
public:

	Playing();
	virtual ~Playing();

	GameState * Update();

private:

	void SetScoreIconLocations();
	void Update_And_Draw_Scoreboard();

	SimpleGameObject * clock;
	Timer * timer;



};

#endif
