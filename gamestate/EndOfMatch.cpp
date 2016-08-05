#include "EndOfMatch.h"



#include "../t3dlib/t3dlib1.h"
#include "../universe/Universe.h"
#include "../input/Keyboard.h"

#include "GameStart.h"


#include <iostream>
#include <sstream>
using namespace std;



void ResetPlayers()
{
	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		next->SetInitialValuesForNewMatch();

	}




}



GameState * EndOfMatch::Update()
{

	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface


	Player * survivor = Universe::GetSurvivingPlayer();


	int survivorId = survivor->GetPlayerType();

	stringstream ss (stringstream::in | stringstream::out);
	ss << survivorId;

	const string message = survivor->GetName() + string(" Player " )  + string(" WON THE MATCH!!!");
	Draw_Text_GDI(message.c_str(),110,240,RGB(255,255,255),lpddsback);


	DDraw_Fill_Surface(lpddsback,backgroundColor );

	DDraw_Flip();

	countdownTimer--;


	if(countdownTimer <= 200)
	{
		Draw_Text_GDI("Press Space bar to restart match",110,120,RGB(255,255,255),lpddsback);
		UCHAR * keyboard_state = Universe::GetKeyboard()->GetKey();

		if (keyboard_state[DIK_SPACE] )
		{
			ResetPlayers();

			delete this;
			return new GameStart();

		}




	}


	return this;

}


