#include "SelectingController.h"


#include "../universe/Universe.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../bob/BlitterObject.h"
#include "GameStart.h"
#include "../input/Keyboard.h"
#include "../input/Joystick.h"


GameState * SelectingController::Update()
{

	{
	Player * computerPlayer = Universe::GetPlayers()[1];
	computerPlayer->SetController(Universe::GetKeyboard());
	}


	{
	Player * humanPlayer = Universe::GetPlayers()[0];
	humanPlayer->SetController(Universe::GetKeyboard());
	}

//	return this->GetNextGameStateAndDeleteCurrentGameState();
	delete this;
	Universe::SetNumberOfRoundsInGame(2);
	return new GameStart();


}




GameState * SelectingController::GetNextGameStateAndDeleteCurrentGameState()
{
	return NULL;
}



SelectingController::SelectingController()
{
	string filename = "bitmaps/PickControl/ChooseControl.bmp";
	gameObject = new SimpleGameObject(70,55, 478,370,filename);

	selectorPosition = 1;
	selectorX = 130;
	selectorYBase = 142;
	maxSelectorPosition = (int)Universe::GetPlayers().size();

	int selectorWidth = 46;
	int selectorHeight = 32;

	UpdateSelectorLocation();

	keyRecentlyPressed = true;
	keyPressedCountdownInitialValue = 25;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;


}










