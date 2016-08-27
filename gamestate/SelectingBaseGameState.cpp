#include "SelectingNumPlayers.h"

//#include "Starting.h"


#include "SelectingNumRounds.h"

#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/Selector.h"
#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"
#include "../input/Keyboard.h"
#include "../input/Joystick.h"
#include "../sound/MSound.h"
#include "GameStart.h"


#include <stdio.h>

#define SUB_STATE_SELECTING 1
#define SUB_STATE_PAUSE_AFTER_SELECTING 2


#include <iostream>
#include <sstream>
using namespace std;

#include "../sound/MSound.h"
#include "../gameobjects/SimpleGameObject.h"


SelectingBaseGameState::SelectingBaseGameState()
{
	subState = SUB_STATE_SELECTING;
	selectorPosition = 1;
	selectorX = 130;
	selectorYIncrement = 47;

	int selectorWidth = 52;
	int selectorHeight = 44;

	selector =  new Selector();
	UpdateSelectorLocation();
	pauseAfterSelectionTimer = 70;

	keyRecentlyPressed = true;
	keyPressedCountdownInitialValue = 25;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;
	

}



void SelectingBaseGameState::UpdateSelectorLocation()
{

	int selectorY = selectorYBase + ((selectorPosition - 1) * selectorYIncrement);
	selector->GetBlitterObject()->Set_Pos(selectorX, selectorY );
}


bool SelectingBaseGameState::HandleKeyboardInput()
{
	bool selectionMade = false;


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


		if(keyboard_state[DIK_DOWNARROW])
		{
			HandleMoveSelectorDown();
		}
		else
		if(keyboard_state[DIK_UPARROW])
		{
			HandleMoveSelectorUp();
		}


		if(keyboard_state[DIK_RETURN])
		{
			selectionMade = true;
		}

	}

	return selectionMade;

}


void SelectingBaseGameState::HandleMoveSelectorUp()
{
	keyRecentlyPressed = true;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;

	if(selectorPosition > 1)
	{
		Sound::PlaySound(Sound::selectorMoved, 1.0f);		
		selectorPosition--;
	}

}


void SelectingBaseGameState::HandleMoveSelectorDown()
{
	keyRecentlyPressed = true;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;

	if(selectorPosition < maxSelectorPosition)
	{
		Sound::PlaySound(Sound::selectorMoved, 1.0f);		
		selectorPosition++;
	}

}


bool SelectingBaseGameState::HandleJoystickInput()
{
	bool selectionMade = false;

	Joystick * primaryJoystick = Joystick::allAttachedJoysticks[0];
	if(!primaryJoystick)
	{
		return selectionMade;
	}

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


		DWORD povState = -1;
		DIJOYSTATE joy_state;

		joy_state = primaryJoystick->GetJoystickState();
		povState = joy_state.rgdwPOV[0];


		switch(povState)
		{
		case POV_NORTH:
			HandleMoveSelectorUp();
			break;

		case POV_SOUTH:
			HandleMoveSelectorDown();
			break;

		}
		if(joy_state.rgbButtons[0] != 0 )
		{
			selectionMade = true;
		}
	}



	return selectionMade;

}



GameState * SelectingBaseGameState::Update()
{


	// clear the drawing surface 
	DWORD backgroundColor = _RGB32BIT(0,0,182,255);
	DDraw_Fill_Surface(lpddsback,backgroundColor );




	if(subState == SUB_STATE_PAUSE_AFTER_SELECTING)
	{
		if(pauseAfterSelectionTimer > 0)
		{
			pauseAfterSelectionTimer--;
		}
		else
		{
			return OnItemSelected();
		}
	}
	else
	{

		UpdateSelectorLocation();

		boolean selectionMadeByKeyboard = HandleKeyboardInput();
//		boolean selectionMadeByJoystick = HandleJoystickInput();
		boolean selectionMadeByJoystick = false;
		if(selectionMadeByKeyboard || selectionMadeByJoystick)
		{
			subState = SUB_STATE_PAUSE_AFTER_SELECTING;
			selector->GetBlitterObject()->Set_Animation(1);
			Sound::PlaySound(Sound::selectionMade, .5f);
		}

	}
	selector->GetBlitterObject()->Animate();
	gameObject->GetBlitterObject()->Draw(lpddsback);
	selector->GetBlitterObject()->Draw(lpddsback);
	Draw_Special();

	DDraw_Flip();

	return this;

}
 

