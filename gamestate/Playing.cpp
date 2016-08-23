#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/Block.h"
#include "../gameobjects/ExplosionPart.h"
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
	soundChannel = Sound::PlaySound(Sound::playing, .5f);
// 	clock = new SimpleGameObject(30,10,30,40,"bitmaps/InGame/Scoreboard/Clock.bmp",_RGB32BIT(0,0,182,0));
// 	timer = new Timer(70,25);
	clock = new SimpleGameObject(10,-40,30,40,"bitmaps/InGame/Scoreboard/Clock.bmp",_RGB32BIT(0,0,182,0));
	timer = new Timer(50,-25);

	SetScoreIconLocations();


}


void Playing::SetScoreIconLocations()
{
	PLAYER_VECTOR::iterator theIterator;

	int playerIndex = 0;


	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;

		int playerType = next->GetPlayerType();
		int x = 135 + (playerType * 65) - 20;
		int y = 15 - 50;

		next->SetScoreIconPos(x,y);
//		next->GetScoreIcon()->GetBlitterObject()->Set_Pos(x,y);
		next->GetScoreShell()->GetBlitterObject()->Set_Pos(x + 40,y + 5);
		next->GetScoreNumber()->GetBlitterObject()->Set_Pos(x + 40, y + 5);

	}

}

Playing::~Playing()
{
	soundChannel->stop();
}



void Update_And_Draw_Blocks()
{

	BLOCK_VECTOR::iterator theBlockIterator;

	for(	theBlockIterator = Universe::GetAllBlocks().begin();
		theBlockIterator != Universe::GetAllBlocks().end();
		)
	{
		Block * nextBlock = *theBlockIterator;

		boolean removeThisBlock =  nextBlock->Update();
		nextBlock->GetBlitterObject()->Draw(lpddsback);
		if(removeThisBlock)
		{
			theBlockIterator = Universe::GetAllBlocks().erase(theBlockIterator);
			delete nextBlock;
		}
		else
		{
			theBlockIterator++;
		}
	}

}


void Update_And_Draw_Powerups()
{
	POWERUP_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPowerups().begin();
		theIterator != Universe::GetPowerups().end();
		theIterator++
		)
	{
		Powerup * next = *theIterator;
		next->GetBlitterObject()->Draw(lpddsback);
		next->GetBlitterObject()->Animate();
	}

}




void Draw_Score(Player * aPlayer, int x, int y)
{
	int wins = aPlayer->GetNumberOfWins();
	string name = aPlayer->GetName();
	stringstream wins_stream (stringstream::in | stringstream::out);
	wins_stream << wins;

	string score = name + string(" ") + wins_stream.str();

	Draw_Text_GDI(score.c_str(),x,y,RGB(255,255,255),lpddsback);

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
// 		int x = (playerIndex * 100) + 50;
// 		Draw_Score(next, x, 30);
		next->GetScoreIcon()->Draw(lpddsback);
		next->GetScoreShell()->Draw(lpddsback);
		next->GetScoreNumber()->Draw(lpddsback);
		playerIndex++;

		if(next->GetPlayerState() == PLAYER_STATE_ALIVE)
		{
			boolean removeThisPlayer =  next->Update();
			next->Draw(lpddsback);
			if(removeThisPlayer)
			{
				next->PlaceExplodingPlayer();
			}

		}
	}

}


void Update_And_Draw_ExplodingPlayers()
{
	EXPLODING_PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetExplodingPlayers().begin();
		theIterator != Universe::GetExplodingPlayers().end();
		)
	{
		ExplodingPlayer * next = *theIterator;

		boolean removeThisExplodingPlayer =  next->Update();

		next->GetBlitterObject()->Draw(lpddsback);
		if(removeThisExplodingPlayer)
		{
			theIterator = Universe::GetExplodingPlayers().erase(theIterator);
			delete next;
		}
		else 
		{
			theIterator++;
		}
	}

}




void Update_And_Draw_Bombs()
{

	BOMB_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetBombs().begin();
		theIterator != Universe::GetBombs().end();
		
		)
	{
		Bomb * nextBomb = *theIterator;

		boolean removeThisBomb =  nextBomb->Update();
		nextBomb->GetBlitterObject()->Draw(lpddsback);
		if(removeThisBomb)
		{
			theIterator = Universe::GetBombs().erase(theIterator);
			delete nextBomb;
		}
		else
		{
			theIterator++;
		}

	}

}



void Update_And_Draw_ExplosionParts()
{

	EXPLOSIONPART_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetExplosionParts().begin();
		theIterator != Universe::GetExplosionParts().end();

		)
	{
		ExplosionPart * nextExplosionPart = *theIterator;

		boolean removeThisExplosion =  nextExplosionPart->Update();
		nextExplosionPart->Draw(lpddsback);
		if(removeThisExplosion)
		{
			theIterator = Universe::GetExplosionParts().erase(theIterator);
			delete nextExplosionPart;
			//theIterator--;
			int numExplosions = (int)Universe::GetExplosionParts().size();
			int x = 3;
		}
		else
		{
			theIterator++;
		}

	}

}



void Playing::Update_And_Draw_Scoreboard()
{
	timer->Draw(lpddsback);
	clock->Draw(lpddsback);

	timer->Update();
}








GameState * Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );


	DWORD scoreboardBackground = _RGB32BIT(0,0,182,0);
	RECT rectangle;

	rectangle.bottom = 50;
	rectangle.top = 0;
	rectangle.right = 640;
	rectangle.left = 0;

	//DDraw_Fill_Surface(lpddsback,scoreboardBackground, &rectangle );

	//Update_And_Draw_Powerups();

	//Update_And_Draw_Blocks();

	//Update_And_Draw_Bombs();

	//Update_And_Draw_ExplosionParts();

	Update_And_Draw_Players();

	//Update_And_Draw_ExplodingPlayers();

	//Update_And_Draw_Scoreboard();

	// flip the surfaces
	DDraw_Flip();


	int numberOfAlivePlayersLeft = Universe::GetNumberOfAlivePlayers();
	int numberOfExplodingPlayers = (int)Universe::GetExplodingPlayers().size();

	if(
		(
			(numberOfAlivePlayersLeft < 2)  &&
			(numberOfExplodingPlayers == 0)
		) 
		||
		timer->Expired()
	  )
	{

		delete this;
		return new EndOfRound();
	}



	return this;

}
