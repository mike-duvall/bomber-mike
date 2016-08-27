#include "SelectingNumPlayers.h"

#include "SelectingController.h"
#include "../universe/Universe.h"
#include "../input/Joystick.h"
#include "../input/Keyboard.h"
#include "../gameobjects/SimpleGameObject.h" 


GameState * SelectingNumPlayers::Update()
{

	bool skip = true;
	if(skip)
	{
		this->HandleSetupPlayers(2);
		return GetNextGameStateAndDeleteCurrentGameState();

	}
	else
	{
		return SelectingBaseGameState::Update();
	}


}



GameState * SelectingNumPlayers::GetNextGameStateAndDeleteCurrentGameState()
{
	delete this;
	return new SelectingController();
}

SelectingNumPlayers::SelectingNumPlayers()
{
	string filename = "bitmaps/Selecting/HowManyPlayers.bmp";
	gameObject = new SimpleGameObject(70,55, 478,370,filename);



	selectorPosition = 1;
	selectorX = 110;
	selectorYBase = 172;
	maxSelectorPosition = 3;

	int selectorWidth = 46;
	int selectorHeight = 32;

	UpdateSelectorLocation();

	keyRecentlyPressed = false;
	keyPressedCountdownInitialValue = 25;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;
	

}

 



GameState * SelectingNumPlayers::OnItemSelected()
{
	this->HandleSetupPlayers(selectorPosition + 1);
	return GetNextGameStateAndDeleteCurrentGameState();

}



void SelectingNumPlayers::HandleSetupPlayers(int numPlayers)
{


	if(numPlayers >= 1)
	{

		Keyboard * aKeyboard = 0;
 		Player * player1 = new Player( 32, 32, WHITE_PLAYER );
		Universe::GetPlayers().push_back( player1 );
	}


	if(numPlayers >= 2)
	{

 		int columnOffset = 13 * 32;
 		int rowOffset = 11 * 32;

		Player * player2 = new Player(columnOffset, rowOffset, BLACK_PLAYER );
		Universe::GetPlayers().push_back( player2 );
	}


}
