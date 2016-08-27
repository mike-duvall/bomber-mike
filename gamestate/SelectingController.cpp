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



}










