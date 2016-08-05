#ifndef SELECTING_NUM_PLAYERS_H
#define SELECTING_NUM_PLAYERS_H



#include "SelectingBaseGameState.h"
#include "../gameobjects/Selector.h"
#include "../fmod//fmod.hpp"

class SelectingNumPlayers : public SelectingBaseGameState
{
public:

	SelectingNumPlayers();

private:

	GameState * OnItemSelected();
 	void HandleSetupPlayers(int numPlayers);
	GameState * GetNextGameStateAndDeleteCurrentGameState();
	GameState * Update();
	FMOD::Channel * soundChannel;


};

#endif
