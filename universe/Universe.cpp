

#include "Universe.h"

#include "Point.h"


using namespace std;


BOMB_VECTOR  Universe::bombs;
POWERUP_VECTOR Universe::powerups;

PLAYER_VECTOR Universe::players;
EXPLODING_PLAYER_VECTOR Universe::explodingPlayers;


Keyboard * Universe::keyboard;
Joystick * Universe::joystick;


int Universe::numberOfRoundsInGame;
int Universe::mapLeftX;
int Universe::mapTopY;






#include "../bob/BlitterObject.h"


void Delete_All_Blocks()
{
}



void Delete_All_ExplodingPlayers()
{
	EXPLODING_PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetExplodingPlayers().begin();
		theIterator != Universe::GetExplodingPlayers().end();
		theIterator++
		)
	{
		ExplodingPlayer * next = *theIterator;
		delete next;

	}
	Universe::GetExplodingPlayers().clear();

}

void Delete_All_ExplosionParts()
{


}

void Delete_All_Powerups()
{
	POWERUP_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPowerups().begin();
		theIterator != Universe::GetPowerups().end();
		theIterator++
		)
	{
		Powerup * next = *theIterator;
		delete next;
	}
	Universe::GetPowerups().clear();
}

// void Delete_All_FlamePowerups()
// {
// 	FLAME_POWERUP_VECTOR::iterator theIterator;
// 
// 	for(	theIterator = Universe::GetFlamePowerups().begin();
// 		theIterator != Universe::GetFlamePowerups().end();
// 		theIterator++
// 		)
// 	{
// 		FlamePowerup * next = *theIterator;
// 		delete next;
// 	}
// 	Universe::GetFlamePowerups().clear();
// }

void Delete_All_Bombs()
{

	BOMB_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetBombs().begin();
		theIterator != Universe::GetBombs().end();
		theIterator++
		)
	{
		Bomb * nextBomb = *theIterator;
		delete nextBomb;

	}

	Universe::GetBombs().clear();
}




void Universe::ClearAndDeleteAll()
{
	Delete_All_Bombs();
	Delete_All_Blocks();
	Delete_All_ExplosionParts();
	Delete_All_Powerups();
// 	Delete_All_BombPowerups();
// 	Delete_All_FlamePowerups();
	Delete_All_ExplodingPlayers();


}






Player * Universe::GetSurvivingPlayer()
{

	Player * survivor = NULL;
	int numSurvivors = 0;

	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		if(next->GetPlayerState() == PLAYER_STATE_ALIVE )
		{
			survivor = next;
			numSurvivors++;
			
		}

	}

	if(numSurvivors == 1)
	{
		return survivor;
	}
	else
	{
		return 0;
	}



}



int Universe::GetNumberOfAlivePlayers()
{
	int numAlivePlayers = 0;


	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		if(next->GetPlayerState() == PLAYER_STATE_ALIVE )
		{
			numAlivePlayers++;
		}

	}

	return numAlivePlayers;

}

void Universe::RemovePowerup(Powerup * aPowerup)
{
	POWERUP_VECTOR::iterator theIterator;
	POWERUP_VECTOR & thPowerups = Universe::GetPowerups();

	for(	theIterator = thPowerups.begin();
		theIterator != thPowerups.end();
		theIterator++
		)
	{
		Powerup * next = *theIterator;
		if(next == aPowerup)
		{
			thPowerups.erase(theIterator);
			return;
		}
	}
}





Point Universe::GetNearestCenterPointFromPoint(int x, int y)
{

	int blockColumn = (x  / MAP_BLOCK_WIDTH) + 1;
	int blockRow = (y / MAP_BLOCK_HEIGHT) + 1;

	int centerX = (blockColumn * MAP_BLOCK_WIDTH) - (MAP_BLOCK_WIDTH / 2);
	int centerY = (blockRow * MAP_BLOCK_HEIGHT) - (MAP_BLOCK_HEIGHT /2 );

	return Point( centerX, centerY );

}



Block * Universe::GetBlockAtPoint(int x, int y)
{

	return NULL;
}

Block * Universe::GetBlockAtGridPoint(int gridX, int gridY)
{
	int x = (gridX * MAP_BLOCK_WIDTH) + (MAP_BLOCK_WIDTH / 2);
	int y = (gridY * MAP_BLOCK_HEIGHT) + (MAP_BLOCK_HEIGHT / 2);
	return Universe::GetBlockAtPoint(x,y);
}




Bomb * Universe::GetBombAtGridPoint(int gridX, int gridY)
{
	int x = (gridX * MAP_BLOCK_WIDTH) + (MAP_BLOCK_WIDTH / 2);
	int y = (gridY * MAP_BLOCK_HEIGHT) + (MAP_BLOCK_HEIGHT / 2);
	return Universe::GetBombAtPoint(x,y);
}



Bomb * Universe::GetBombAtPoint(int x, int y)
{
	Bomb * foundBomb = 0;
	BOMB_VECTOR::iterator theBombIterator;

	BOMB_VECTOR & theBombs = Universe::GetBombs();

	int t = 0;
	for(	theBombIterator = theBombs.begin();
		theBombIterator != theBombs.end();
		theBombIterator++
		)
	{
		t++;
		Bomb * nextBomb = *theBombIterator;
		if(nextBomb->IsPointInBomb(x,y))
		{
			if(foundBomb)
			{
				// shouldn't hit this point
				int x = 3;
			}
			foundBomb = nextBomb;
		}
	}


	return foundBomb;

}






void Universe::RemoveBlock(Block * aBlock)
{


}


