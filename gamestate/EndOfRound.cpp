#include "EndOfRound.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/Block.h"
#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"

#include "EndOfRoundReport.h"

extern void Draw_Score(Player * aPlayer, int x, int y);


void Draw_Blocks()
{

	BLOCK_VECTOR::iterator theBlockIterator;

	for(	theBlockIterator = Universe::GetAllBlocks().begin();
		theBlockIterator != Universe::GetAllBlocks().end();
		theBlockIterator++
		)
	{
		Block * nextBlock = *theBlockIterator;
		nextBlock->GetBlitterObject()->Draw(lpddsback);
	}

}


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
		Draw_Score(next, x, 30);
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

 	Draw_Blocks();

	Draw_Players();


	// flip the surfaces
	DDraw_Flip();

	countDownTimer--;

	if(countDownTimer < 1)
	{
		Player * survivor = Universe::GetSurvivingPlayer();
		if(survivor)
		{
			int numberOfSurvivorWins = survivor->GetNumberOfWins();
			numberOfSurvivorWins++;
			survivor->SetNumberofWins(numberOfSurvivorWins);

		}

		return new EndOfRoundReport();
	}

	return this;

}
