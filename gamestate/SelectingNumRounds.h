#ifndef SELECTING_NUM_ROUNDS_H
#define SELECTING_NUM_ROUNDS_H



#include "GameState.h"
#include "../gameobjects/Selector.h"
#include "../fmod//fmod.hpp"
#include "SelectingBaseGameState.h"

class SelectingNumRounds : public SelectingBaseGameState
{
public:


	SelectingNumRounds(	FMOD::Channel * aSoundChannel);

private:

	GameState * OnItemSelected();
	GameState * Update();
	FMOD::Channel * soundChannel;


};

#endif
