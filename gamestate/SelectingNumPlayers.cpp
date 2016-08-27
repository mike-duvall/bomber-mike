#include "SelectingNumPlayers.h"

#include "../universe/Universe.h"
#include "../input/Keyboard.h"



GameState * SelectingNumPlayers::Update()
{

	Keyboard * aKeyboard = 0;
	Player * player1 = new Player(32, 32, WHITE_PLAYER);
	Universe::GetPlayers().push_back(player1);

	int columnOffset = 13 * 32;
	int rowOffset = 11 * 32;

	Player * player2 = new Player(columnOffset, rowOffset, BLACK_PLAYER);
	Universe::GetPlayers().push_back(player2);

	{
	Player * computerPlayer = Universe::GetPlayers()[1];
	computerPlayer->SetController(Universe::GetKeyboard());
	}


	{
	Player * humanPlayer = Universe::GetPlayers()[0];
	humanPlayer->SetController(Universe::GetKeyboard());
	}

	delete this;
	Universe::SetNumberOfRoundsInGame(2);
	return new GameStart();

}







