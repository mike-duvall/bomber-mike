

#include "Universe.h"

#include "Point.h"


using namespace std;


PLAYER_VECTOR Universe::players;


Keyboard * Universe::keyboard;
Joystick * Universe::joystick;


int Universe::numberOfRoundsInGame;
int Universe::mapLeftX;
int Universe::mapTopY;






#include "../bob/BlitterObject.h"


void Delete_All_Blocks()
{
}



void Delete_All_ExplosionParts()
{


}



void Universe::ClearAndDeleteAll()
{
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






void Universe::RemoveBlock(Block * aBlock)
{


}


