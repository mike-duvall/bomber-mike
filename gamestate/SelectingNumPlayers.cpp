#include "SelectingNumPlayers.h"

#include "../universe/Universe.h"
#include "../input/Joystick.h"
#include "../input/Keyboard.h"
#include "../gameobjects/SimpleGameObject.h" 


GameState * SelectingNumPlayers::Update()
{

	this->HandleSetupPlayers(2);
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



SelectingNumPlayers::SelectingNumPlayers()
{
	

}




void SelectingNumPlayers::HandleSetupPlayers(int numPlayers)
{

	Keyboard * aKeyboard = 0;
 	Player * player1 = new Player( 32, 32, WHITE_PLAYER );
	Universe::GetPlayers().push_back( player1 );

 	int columnOffset = 13 * 32;
 	int rowOffset = 11 * 32;

	Player * player2 = new Player(columnOffset, rowOffset, BLACK_PLAYER );
	Universe::GetPlayers().push_back( player2 );

}
