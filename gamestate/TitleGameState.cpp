#include "TitleGameState.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects//SimpleGameObject.h"
#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"
#include "../input/Keyboard.h"
#include "../input/Joystick.h"
#include "SelectingNumPlayers.h"





TitleGameState::TitleGameState()
{

	subState = SUB_STATE_BLACK_MOVING;
	titleX = 50;
	titleY = 20;
	blackBombermanTimer = 40;
	whiteBombermanStartTimer = blackBombermanTimer;
	whiteBombermanTimer = 40;
	blackPlayer = new SimpleGameObject(titleX + 10 ,titleY - 172,122,146,"bitmaps/IntroPlayerBlack.bmp");
	whitePlayer = new SimpleGameObject(640 + 140 ,titleY + 212,178,198,"bitmaps/IntroPlayerWhite.bmp");
	title = 0;
	yearTitle = 0;
	clonedBy = 0;
	mikeDuVall = 0;
	pushButton = 0;

}


TitleGameState::~TitleGameState()
{
	delete blackPlayer;
}


void MoveBlitterObject(BlitterObject * aBlitterObject, int dx, int dy)
{
	int currentX = aBlitterObject->GetX();
	int currentY = aBlitterObject->GetY();
	currentX += dx;
	currentY += dy;

	aBlitterObject->Set_Pos(currentX, currentY);

}



void TitleGameState::HandleWhiteMoving()
{
	whiteBombermanTimer--;
	MoveBlitterObject(whitePlayer->GetBlitterObject(),-10,0);
	if(whiteBombermanTimer <=0)
	{
		subState = SUB_STATE_TITLE_MOVING;
	}

}


void TitleGameState::HandleBlackMoving()
{
	blackBombermanTimer--;

	MoveBlitterObject(blackPlayer->GetBlitterObject(),0,10);
	if(blackBombermanTimer <= 0)
	{
		subState = SUB_STATE_WHITE_MOVING;
	}

}



void TitleGameState::HandleTitleMoving()
{
	if(title == 0)
	{
		titleMovingTimer = 50;
		title = new SimpleGameObject(titleX,titleY,512,448,"bitmaps/MainTitle.bmp");
		bomberTitle = new SimpleGameObject(600,75,274,116,"bitmaps/BomberTitle.bmp",_RGB32BIT(0,1,217,138));
		manTitle = new SimpleGameObject(730,140,186,72,"bitmaps/ManTitle.bmp",_RGB32BIT(0,1,217,138));

	}


	MoveBlitterObject(bomberTitle->GetBlitterObject(),-10, 0);
	MoveBlitterObject(manTitle->GetBlitterObject(),-10, 0);


	titleMovingTimer--;
	if(titleMovingTimer <= 0)
	{
		subState = SUB_STATE_ANIMATING_CREDITS;
		waitForCreditsTimer = 200;
	}

}





void TitleGameState::HandleAnimatingCredits()
{
	if(yearTitle == 0)
	{
		yearTitle = new SimpleGameObject(375,90,154,126,"bitmaps/93-Title.bmp",_RGB32BIT(0,1,217,138));
	}

	if(waitForCreditsTimer > 0)
	{
		waitForCreditsTimer--;
		return;
	}

	if(clonedBy == 0)
	{
		clonedBy = new SimpleGameObject(700,400,87,24,"bitmaps/Cloned by.bmp",_RGB32BIT(0,36,0,109));
		cloneByTimer = 33;
		preDuVallTimer = 75;

	}


	if(cloneByTimer > 0)
	{
		cloneByTimer--;
		MoveBlitterObject(clonedBy->GetBlitterObject(),-15, 0);
	}
	else
	if (preDuVallTimer > 0)
	{
		preDuVallTimer--;
	}
	else
	{
		if(mikeDuVall == 0)
		{
			mikeDuVall = new SimpleGameObject(-150,425,169,24,"bitmaps/Mike DuVall.bmp",_RGB32BIT(0,36,0,109));
			mikeDuVallTimer = 26;
		}

		if(mikeDuVallTimer > 0)
		{
			mikeDuVallTimer--;
			MoveBlitterObject(mikeDuVall->GetBlitterObject(),12, 0);
		}
		else
		{
			subState = SUB_STATE_ANIMATING_FASHIZZLE;
			preFashizzleCountdownTimer = 70;
		}
	}


}


void TitleGameState::HandleAnimatingFashizzle()
{

	if(pushButton == 0)
	{
	pushButton = new SimpleGameObject(190,280,192,16,"bitmaps/PushButton.bmp",_RGB32BIT(0,36,0,109));
	}

	if(preFashizzleCountdownTimer < 0)
	{
		preFashizzleCountdownTimer--;

	}
	else
	{
		if(fashizzle == 0)
		{
		fashizzle = new SimpleGameObject(-30,425,63,10,"bitmaps/Fashizzle.bmp",_RGB32BIT(0,36,0,109));
		}

	}
}


void TitleGameState::HandleDisplayingMenu()
{

}

void DrawIfNotNull(SimpleGameObject * aSimpleGameObject)
{
	if(aSimpleGameObject)
	{
		aSimpleGameObject->GetBlitterObject()->Draw(lpddsback);
	}

}



GameState * TitleGameState::Update()
{
	bool skip = false;
	if(skip)
	{
		delete this;
		return new SelectingNumPlayers();

	}

	DWORD backgroundColor = _RGB32BIT(0,0,0,0);


	switch(subState)
	{
	case SUB_STATE_BLACK_MOVING:
		HandleBlackMoving();
		break;

	case SUB_STATE_WHITE_MOVING:
		HandleWhiteMoving();
		break;

	case SUB_STATE_TITLE_MOVING:
		HandleTitleMoving();
		break;


	case SUB_STATE_ANIMATING_CREDITS:
		HandleAnimatingCredits();
		break;

	case SUB_STATE_ANIMATING_FASHIZZLE:
		HandleAnimatingFashizzle();
		break;


	case SUB_STATE_DISPLAYING_MENU:
		HandleDisplayingMenu();
		break;



	}

	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );
	blackPlayer->GetBlitterObject()->Draw(lpddsback);
	whitePlayer->GetBlitterObject()->Draw(lpddsback);
	if(title)
	{
		title->GetBlitterObject()->Draw(lpddsback);
		bomberTitle->GetBlitterObject()->Draw(lpddsback);
		manTitle->GetBlitterObject()->Draw(lpddsback);
		
	}

	DrawIfNotNull(yearTitle);
	DrawIfNotNull(clonedBy);
	DrawIfNotNull(mikeDuVall);
	DrawIfNotNull(pushButton );


	UCHAR * keyboard_state = Universe::GetKeyboard()->GetKey();

	boolean joystickButtonPressed = false;

	//Joystick * primaryJoystick = Joystick::allAttachedJoysticks[0];
	//if(primaryJoystick)
	//{
	//	DIJOYSTATE joy_state = primaryJoystick->GetJoystickState();
	//	if(joy_state.rgbButtons[0] != 0 )
	//	{
	//		joystickButtonPressed = true;
	//	}

	//}



	if (keyboard_state[DIK_SPACE] || joystickButtonPressed )
	{
		delete this;
		return new SelectingNumPlayers();

	}


	// flip the surfaces
	DDraw_Flip();

	return this;

}
