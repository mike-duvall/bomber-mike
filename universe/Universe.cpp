

#include "Universe.h"

#include "Point.h"


using namespace std;

BLOCK_VECTOR  Universe::blocks;

BOMB_VECTOR  Universe::bombs;
EXPLOSIONPART_VECTOR  Universe::explosionParts;
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
	BLOCK_VECTOR::iterator theBlockIterator;

	for(	theBlockIterator = Universe::GetAllBlocks().begin();
		theBlockIterator != Universe::GetAllBlocks().end();
		theBlockIterator++
		)
	{
		Block * nextBlock = *theBlockIterator;
		delete nextBlock;
	}

	Universe::GetAllBlocks().clear();
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

	EXPLOSIONPART_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetExplosionParts().begin();
		theIterator != Universe::GetExplosionParts().end();
		theIterator++
		)
	{
		ExplosionPart * nextExplosionPart = *theIterator;
		delete nextExplosionPart;

	}
	Universe::GetExplosionParts().clear();

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
	Block * foundBlock = 0;
	BLOCK_VECTOR::iterator theBlockIterator;

	BLOCK_VECTOR & theBlocks = Universe::GetAllBlocks();

	int t = 0;
	for(	theBlockIterator = theBlocks.begin();
		theBlockIterator != theBlocks.end();
		theBlockIterator++
		)
	{
		t++;
		Block * nextBlock = *theBlockIterator;
		if(nextBlock->IsPointInBlock(x,y))
		{
			if(foundBlock)
			{
				// shouldn't hit this point
				int x = 3;
			}
			foundBlock = nextBlock;
		}
	}


	return foundBlock;

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


ExplosionPart * Universe::GetExplosionPartAtGridPoint(int gridX, int gridY)
{
	int x = (gridX * MAP_BLOCK_WIDTH) + (MAP_BLOCK_WIDTH / 2);
	int y = (gridY * MAP_BLOCK_HEIGHT) + (MAP_BLOCK_HEIGHT / 2);
	return Universe::GetExplosionPartAtPoint(x,y);
}



 ExplosionPart * Universe::GetExplosionPartAtPoint(int x, int y)
{
	ExplosionPart * foundExplosionPart = 0;
	EXPLOSIONPART_VECTOR::iterator theExplosionPartIterator;

	EXPLOSIONPART_VECTOR & theExplosionParts = Universe::GetExplosionParts();

	int t = 0;
	for(	theExplosionPartIterator = theExplosionParts.begin();
		theExplosionPartIterator != theExplosionParts.end();
		theExplosionPartIterator++
		)
	{
		t++;
		ExplosionPart * nextExplosionPart = *theExplosionPartIterator;
		if(nextExplosionPart->IsPointInExplosionPartSquare(x,y))
		{
			if(foundExplosionPart)
			{
				// shouldn't hit this point
				int x = 3;
			}
			foundExplosionPart = nextExplosionPart;
		}
	}
	return foundExplosionPart;
}




void Universe::RemoveBlock(Block * aBlock)
{
	BLOCK_VECTOR::iterator theBlockIterator;

	BLOCK_VECTOR & theBlocks = Universe::GetAllBlocks();

	for(	theBlockIterator = theBlocks.begin();
		theBlockIterator != theBlocks.end();
		theBlockIterator++
		)
	{

		Block * nextBlock = *theBlockIterator;
		if(nextBlock == aBlock)
		{
			theBlocks.erase(theBlockIterator);
			return;

		}
	}



}


