#include "SelectingController.h"


#include "../universe/Universe.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../bob/BlitterObject.h"
#include "GameStart.h"
#include "../input/Keyboard.h"
#include "../input/Joystick.h"


GameState * SelectingController::Update()
{

	bool skip = true;
	if(skip)
	{
		{
		Player * computerPlayer = Universe::GetPlayers()[1];
		computerPlayer->SetController(Universe::GetKeyboard());
		}


		{
		Player * humanPlayer = Universe::GetPlayers()[0];
		humanPlayer->SetController(Universe::GetKeyboard());
		//humanPlayer->SetController(new ComputerController(humanPlayer));
		}

// 		{
// 			Player * computerPlayer = Universe::GetPlayers()[2];
// 			computerPlayer->SetController(new ComputerController(computerPlayer));
// 		}
// 
// 		{
// 			Player * computerPlayer = Universe::GetPlayers()[3];
// 			computerPlayer->SetController(new ComputerController(computerPlayer));
// 		}



		return this->GetNextGameStateAndDeleteCurrentGameState();

	}
	else
	{
		GameState * nextGameState = SelectingBaseGameState::Update();
		return nextGameState;
	}


	

}


void SelectingController::Draw_Special()
{
	this->Draw_PlayerIcons();
	this->Draw_BomberIcons();
	this->Draw_ControllerSelectors();
}


GameState * SelectingController::GetNextGameStateAndDeleteCurrentGameState()
{
	delete this;
	Universe::SetNumberOfRoundsInGame(2);
	return new GameStart();
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
	
	Create_PlayerIcons();

}


void SelectingController::Create_IconsForPlayer(const string & playerNumber,  int x, int y)
{

	string bitmapFileName = "bitmaps/PickControl/PickControl_Player" + playerNumber + ".bmp";
	SimpleGameObject * playerIcon = new SimpleGameObject(x,y,80,38,bitmapFileName,1);
	playerIcons.push_back(playerIcon);

	string bomberBitmapFileName = "bitmaps/PickControl/Bomber.bmp";
	SimpleGameObject * bomberIcon = new SimpleGameObject(x + 85,y + 10,146,30,bomberBitmapFileName,1);
	this->bomberIcons.push_back(bomberIcon);

	ControllerSelector * theControllerSelector = new ControllerSelector(x + 240, y + 8);
	controllerSelectors.push_back(theControllerSelector);

}


void SelectingController::HandleIncrementSelectedController()
{
	keyRecentlyPressed = true;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;

	ControllerSelector * currentControllerSelector = controllerSelectors[selectorPosition - 1];
	int currentSelection =  currentControllerSelector->GetSelection();
	switch(currentSelection)
	{
	case 1:
		currentSelection = 2;
		break;

	case 2:
		currentSelection = 3;
		break;

	case 3:
		break;
	}
	currentControllerSelector->SetSelection(currentSelection);
}


void SelectingController::HandleDecrementSelectedController()
{
	keyRecentlyPressed = true;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;

	ControllerSelector * currentControllerSelector = controllerSelectors[selectorPosition - 1];
	int currentSelection =  currentControllerSelector->GetSelection();
	switch(currentSelection)
	{
	case 1:
		break;

	case 2:
		currentSelection = 1;
		break;

	case 3:
		currentSelection = 2;
		break;
	}
	currentControllerSelector->SetSelection(currentSelection);

}



bool SelectingController::HandleKeyboardInput()
{
	bool selected = SelectingBaseGameState::HandleKeyboardInput();

	if(keyRecentlyPressed)
	{
		keyPresseedCountdownTimer--;
		if(keyPresseedCountdownTimer <= 0)
		{
			keyRecentlyPressed = false;
		}
	}
	else
	{

		UCHAR * keyboard_state = Universe::GetKeyboard()->GetKey();

		if(keyboard_state[DIK_RIGHTARROW])
		{
			HandleIncrementSelectedController();
		}
		else if(keyboard_state[DIK_LEFTARROW] )
		{
			HandleDecrementSelectedController();
		}

	}

	return selected;
}


void SelectingController::Create_PlayerIcons()
{

	int x = 185;
	int y = 150;

	string playerNumber = "1";
	this->Create_IconsForPlayer(playerNumber, x, y);

	playerNumber = "2";
	y += selectorYIncrement;
	this->Create_IconsForPlayer(playerNumber, x, y);

	int numberOfPlayers = (int)Universe::GetPlayers().size();

	if(numberOfPlayers > 2)
	{
		playerNumber = "3";
		y += selectorYIncrement;
		this->Create_IconsForPlayer(playerNumber, x, y);
	}

	if(numberOfPlayers > 3)
	{
		playerNumber = "4";
		y += selectorYIncrement;
		this->Create_IconsForPlayer(playerNumber, x, y);
	}
}


void SelectingController::Draw_PlayerIcons()
{

	SIMPLE_GAME_OBJECT_VECTOR ::iterator theIterator;

	for(	theIterator = playerIcons.begin();
		theIterator != playerIcons.end();
		theIterator++
		)
	{
		SimpleGameObject * next = *theIterator;
		next->GetBlitterObject()->Draw(lpddsback);
	}


}


void SelectingController::Draw_BomberIcons()
{

	SIMPLE_GAME_OBJECT_VECTOR ::iterator theIterator;

	for(	theIterator = bomberIcons.begin();
		theIterator != bomberIcons.end();
		theIterator++
		)
	{
		SimpleGameObject * next = *theIterator;
		next->GetBlitterObject()->Draw(lpddsback);

	}


}


void SelectingController::Draw_ControllerSelectors()
{

	CONTROLLER_SELECT_VECTOR ::iterator theIterator;

	for(	theIterator = controllerSelectors.begin();
		theIterator != controllerSelectors.end();
		theIterator++
		)
	{
		ControllerSelector * next = *theIterator;
		next->Draw(lpddsback);
	}


}





GameState * SelectingController::OnItemSelected()
{

	CONTROLLER_SELECT_VECTOR ::iterator theIterator;

	int playerNumber = 0;
	int joystickIndex = 0;

	for(	theIterator = controllerSelectors.begin();
		theIterator != controllerSelectors.end();
		theIterator++
		)
	{
		ControllerSelector * next = *theIterator;
		int selection = next->GetSelection();
		Player * thePlayer = Universe::GetPlayers()[playerNumber];
		switch(selection)
		{

		case CONTROLLER_KEYBOARD:
			thePlayer->SetController(Universe::GetKeyboard());
			break;

		}
		playerNumber++;


	}


	return this->GetNextGameStateAndDeleteCurrentGameState();
}

