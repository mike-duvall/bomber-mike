#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/Block.h"
#include "../gameobjects/ExplodingPlayer.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../gameobjects/Timer.h"
#include "../gameobjects/Number.h"


#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"
#include "../gamestate/EndOfRound.h"

#include <iostream>
#include <sstream>
using namespace std;

#include "../sound/MSound.h"

// Dummy change

Playing::Playing()
{

}


Playing::~Playing()
{
}




void Update_And_Draw_Players()
{

	PLAYER_VECTOR::iterator theIterator;

	int playerIndex = 0;
	

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		playerIndex++;

		if(next->GetPlayerState() == PLAYER_STATE_ALIVE)
		{
			boolean removeThisPlayer =  next->Update();
			next->Draw(lpddsback);

		}
	}

}





GameState * Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Update_And_Draw_Players();

	DDraw_Flip();

	return this;

}
