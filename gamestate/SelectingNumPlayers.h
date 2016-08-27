#ifndef SELECTING_NUM_PLAYERS_H
#define SELECTING_NUM_PLAYERS_H




#include "../gameobjects/Selector.h"
#include "../gamestate/GameStart.h"

class SelectingNumPlayers : public GameState
{
public:

	SelectingNumPlayers();

private:


 	void HandleSetupPlayers(int numPlayers);

	GameState * Update();
	

};

#endif
