#ifndef GAMESTART_H
#define GAMESTART_H



#include "GameState.h"



class SimpleGameObject;

class GameStart : public GameState
{
public:

	GameStart();
	GameState * Update();

private:

	int numberOfPlayers;
	int numberOfRounds;

};

#endif
