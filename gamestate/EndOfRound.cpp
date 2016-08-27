#include "EndOfRound.h"


#include "../t3dlib/t3dlib1.h"

#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"


extern void Draw_Score(Player * aPlayer, int x, int y);


void Draw_Players()
{

	int playerIndex = 0;
	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{

		Player * next = *theIterator;
		int x = (playerIndex * 100) + 50;
		playerIndex++;

		if(next->GetPlayerState() == PLAYER_STATE_ALIVE)
		{
			next->Draw(lpddsback);
		}


	}

}





GameState * EndOfRound::Update()
{
	int backgroundColor = 122;
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Draw_Players();

	// flip the surfaces
	DDraw_Flip();

	countDownTimer--;

	return this;

}
