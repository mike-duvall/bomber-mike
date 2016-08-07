#include "SelectingNumPlayers.h"

#include "SelectingController.h"
#include "../universe/Universe.h"
#include "../input/Joystick.h"
#include "../input/Keyboard.h"
#include "../gameobjects/SimpleGameObject.h" 
#include "../sound/MSound.h"


GameState * SelectingNumPlayers::Update()
{

	bool skip = false;
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
	// get pointer on the stack to soundChannel before
	// deleting this
	FMOD::Channel * tempSoundChannel = soundChannel;
	delete this;
	return new SelectingController(tempSoundChannel);
}

SelectingNumPlayers::SelectingNumPlayers()
{
	string filename = "Selecting/HowManyPlayers.bmp";
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
	
	soundChannel = Sound::PlaySound(Sound::pickingStuff, .5f);
	int x = 3;

}

 



GameState * SelectingNumPlayers::OnItemSelected()
{
	this->HandleSetupPlayers(selectorPosition + 1);
	return GetNextGameStateAndDeleteCurrentGameState();
// 	FMOD::Channel * tempSoundChannel = soundChannel;
// 	delete this;
// 	return new SelectingNumRounds(tempSoundChannel);

}



void SelectingNumPlayers::HandleSetupPlayers(int numPlayers)
{


	if(numPlayers >= 1)
	{
// 		Joystick * theJoystick = 0;
// 		if(Joystick::numJoysticks >= 1)
// 		{
// 			theJoystick = Joystick::allAttachedJoysticks[0];
// 		}

		Keyboard * aKeyboard = 0;
 		Player * player1 = new Player( 32, 32, WHITE_PLAYER );
//		player1->SetController( Universe::GetKeyboard() );
		Universe::GetPlayers().push_back( player1 );
	}


	if(numPlayers >= 2)
	{
// 		Joystick * theJoystick = 0;
// 		if(Joystick::numJoysticks >= 2)
// 		{
// 			theJoystick = Joystick::allAttachedJoysticks[1];
// 		}

 		int columnOffset = 13 * 32;
 		int rowOffset = 11 * 32;

// 		int columnOffset = 2 * 32;
// 		int rowOffset = 5 * 32;

// 		int columnOffset = 1 * 32;
// 		int rowOffset = 4 * 32;



		Player * player2 = new Player(columnOffset, rowOffset, BLACK_PLAYER );
//		player2->SetController(theJoystick);
		Universe::GetPlayers().push_back( player2 );
	}

	if(numPlayers >= 3)
	{
		int columnOffset = 13 * 32;
		int rowOffset = 1 * 32;
		Player * player3 = new Player(columnOffset,  rowOffset, RED_PLAYER );
//		player3->SetController( Joystick::allAttachedJoysticks[2]);
		Universe::GetPlayers().push_back( player3 );
	}


	if(numPlayers >= 4)
	{
		int columnOffset = 1 * 32;
		int rowOffset = 11 * 32;
		Player * player4 = new Player(columnOffset, rowOffset, BLUE_PLAYER  );
//		player4->SetController( Joystick::allAttachedJoysticks[3]);
		Universe::GetPlayers().push_back( player4 );
	}



}
