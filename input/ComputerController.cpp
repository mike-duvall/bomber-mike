#include "ComputerController.h"



#include "../t3dlib/t3dlib1.h"


#include <cstdlib>
#include <ctime> 
#include <math.h>
#include <sstream>


#include "../gameobjects/ControlEvent.h"
#include "../universe/Universe.h"
#include "../universe/Point.h"
#include "../bob/BlitterObject.h"


#include "../ai/PathFinder.h"




ComputerController::ComputerController(Player * aPlayer)
{
	myPlayer = aPlayer;
	selectedEnemy = 0;
	guidanceCountdownTimer = 0;
	previousBestNodeX = -1;
	previousBestNodeY = -1;


}


ComputerController::~ComputerController()
{
}




int AS_Valid(_asNode *parent, _asNode *node, int data, void *pointer) 
{

    if( 
		(parent->x - node->x != 0) &&
		(parent->y - node->y != 0)
      )
	{
		return FALSE;
	}


	Block * aBlock = Universe::GetBlockAtPoint(node->x * MAP_BLOCK_WIDTH, node->y * MAP_BLOCK_HEIGHT );

	if( aBlock != 0)
	{
		return FALSE;
	}


	return FALSE;
}

int AS_Cost(_asNode *parent, _asNode *node, int data, void *pointer) 
{
	ComputerController *me = reinterpret_cast<ComputerController *>(pointer);

	int halfBlockWidth = MAP_BLOCK_WIDTH / 2;
	int halfBlockHeight = MAP_BLOCK_HEIGHT / 2;


	Player * enemyPlayer = me->GetSelectedEnemy();

	int playerX = enemyPlayer->GetCollisionBox().left;
	int playerY = enemyPlayer->GetCollisionBox().top;

	playerX += MAP_BLOCK_WIDTH / 2;
	playerY += MAP_BLOCK_HEIGHT / 2;

	int blockHorizontalOffset = playerX / MAP_BLOCK_WIDTH;
	int blockVerticalOffset = playerY/ MAP_BLOCK_HEIGHT;


	int cost = abs(blockHorizontalOffset - node->x) + abs(blockVerticalOffset - node->y);

	return cost;

}



_asNode * FindFirstStep(_asNode * bestNode)
{
	_asNode * currentNode = bestNode;
	_asNode * firstStepAfterParent = 0;
	while(currentNode->parent != 0)
	{
		firstStepAfterParent = currentNode;
		currentNode = currentNode->parent;


	}

	return firstStepAfterParent;
}







float ComputerController::DistanceBetweenTwoPoints(int x1, int y1, int x2, int y2 )
{

	int xd = x2-x1;
	int yd = y2-y1;

	float distance = sqrt(float(xd*xd + yd*yd));

	return distance;

}



int ComputerController::CalculateDistanceToPlayer(Player * anEnemyPlayer)
{

	int x1 = this->myPlayer->GetBlitterObject()->GetX();
	int y1 = this->myPlayer->GetBlitterObject()->GetY();

	int x2 = anEnemyPlayer->GetBlitterObject()->GetX();
	int y2 = anEnemyPlayer->GetBlitterObject()->GetY();


	int xd = x2-x1;
	int yd = y2-y1;

	int distance = int(sqrt(float(xd*xd + yd*yd)));

	return distance;

}


int ComputerController::HandleStandingOnBomb()
{
	RECT myPlayerCollisionBoxRect = myPlayer->GetCollisionBox();
	int thePlayerX = myPlayerCollisionBoxRect.left;
	int thePlayerY = myPlayerCollisionBoxRect.top;

	Block * foundBlock = Universe::GetBlockAtPoint(thePlayerX - MAP_BLOCK_WIDTH, thePlayerY);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_WEST;
	}
	foundBlock = Universe::GetBlockAtPoint(thePlayerX + MAP_BLOCK_WIDTH, thePlayerY);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_EAST;
	}
	foundBlock = Universe::GetBlockAtPoint(thePlayerX, thePlayerY - MAP_BLOCK_HEIGHT);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_NORTH;
	}
	foundBlock = Universe::GetBlockAtPoint(thePlayerX, thePlayerY + MAP_BLOCK_HEIGHT);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_SOUTH;
	}

	return CONTROL_EVENT_DO_NOTHING;

}

int ComputerController::HandleSameRowAsBomb()
{
	RECT myPlayerCollisionBoxRect = myPlayer->GetCollisionBox();
	int thePlayerX = myPlayerCollisionBoxRect.left;
	int thePlayerY = myPlayerCollisionBoxRect.top;

	Block * foundBlock = Universe::GetBlockAtPoint(thePlayerX, thePlayerY - MAP_BLOCK_HEIGHT);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_NORTH;
	}
	foundBlock = Universe::GetBlockAtPoint(thePlayerX, thePlayerY + MAP_BLOCK_HEIGHT);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_SOUTH;
	}

	return CONTROL_EVENT_DO_NOTHING;
}

int ComputerController::HandleSameColumnAsBomb()
{
	RECT myPlayerCollisionBoxRect = myPlayer->GetCollisionBox();
	int thePlayerX = myPlayerCollisionBoxRect.left;
	int thePlayerY = myPlayerCollisionBoxRect.top;

	Block * foundBlock = Universe::GetBlockAtPoint(thePlayerX - MAP_BLOCK_WIDTH, thePlayerY);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_WEST;
	}
	foundBlock = Universe::GetBlockAtPoint(thePlayerX + MAP_BLOCK_WIDTH, thePlayerY);
	if(foundBlock == 0)
	{
		return CONTROL_EVENT_MOVE_EAST;
	}

	return CONTROL_EVENT_DO_NOTHING;
}

GameObject * ComputerController::GetGameObjectAtPoint( int x, int y)
{

	GameObject * foundGameObject = 0;



	return foundGameObject;



}




int ComputerController::RunFromBomb( Bomb * aBomb )
{

	int controlEvent = CONTROL_EVENT_DO_NOTHING;
	int theBombX = aBomb->GetBlitterObject()->GetX();
	int theBombY = aBomb->GetBlitterObject()->GetY();

	RECT myPlayerCollisionBoxRect = myPlayer->GetCollisionBox();
	int thePlayerX = myPlayerCollisionBoxRect.left;
	int thePlayerY = myPlayerCollisionBoxRect.top;

	if(theBombX > thePlayerX )
	{
		controlEvent = CONTROL_EVENT_MOVE_WEST;
	}
	else if(theBombX < thePlayerX  )
	{
		controlEvent = CONTROL_EVENT_MOVE_EAST;
	}
	else if(theBombY < thePlayerY )
	{
		controlEvent = CONTROL_EVENT_MOVE_SOUTH;
	}
	else if(theBombY > thePlayerY )
	{
		controlEvent = CONTROL_EVENT_MOVE_NORTH;
	}
	else
	{
		// right on top of bomb
		controlEvent = HandleStandingOnBomb();
	}

	if(
		(thePlayerX == lastX) &&
		(thePlayerY == lastY) &&
			(
				(lastControlEvent == CONTROL_EVENT_MOVE_WEST) ||
				(lastControlEvent == CONTROL_EVENT_MOVE_EAST) 
			)
		)
	{
		if(theBombY < thePlayerY )
		{
			controlEvent = CONTROL_EVENT_MOVE_SOUTH;
		}
		else if(theBombY > thePlayerY )
		{
			controlEvent = CONTROL_EVENT_MOVE_NORTH;
		}
		else
		{
			controlEvent = HandleSameRowAsBomb();
		}
	}

	if(
		(thePlayerX == lastX) &&
		(thePlayerY == lastY) &&
		(
		(lastControlEvent == CONTROL_EVENT_MOVE_NORTH) ||
		(lastControlEvent == CONTROL_EVENT_MOVE_SOUTH) 
		)
		)
	{
		if(theBombX < thePlayerX )
		{
			controlEvent = CONTROL_EVENT_MOVE_EAST;
		}
		else if(theBombX > thePlayerX )
		{
			controlEvent = CONTROL_EVENT_MOVE_WEST;
		}
		else
		{
			controlEvent = HandleSameColumnAsBomb();
		}

	}


	return controlEvent;


}


bool DoesPlayerHaveActiveBombs(Player * aPlayer)
{
	BOMB_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetBombs().begin();
		theIterator != Universe::GetBombs().end();
		theIterator++
		)
	{
		Bomb * nextBomb = *theIterator;
		if(nextBomb->GetPlayer() == aPlayer)
		{
			return true;
		}

	}

	return false;
}


Bomb * ComputerController::GetBombCloseToMe()
{
	RECT myPlayerCollisionBoxRect = myPlayer->GetCollisionBox();
	int thePlayerX = myPlayerCollisionBoxRect.left;
	int thePlayerY = myPlayerCollisionBoxRect.top;


	BOMB_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetBombs().begin();
		theIterator != Universe::GetBombs().end();
		theIterator++
		)
	{
		Bomb * nextBomb = *theIterator;
		
		float  distance = DistanceBetweenTwoPoints(thePlayerX,thePlayerY, nextBomb->GetBlitterObject()->GetX(), nextBomb->GetBlitterObject()->GetY());
		if(distance < 200)
		{
			return nextBomb;
		}

	}

	return 0;

}







int ComputerController::GetNumberOfAlivePlayers()
{
	int nummberOfAlivePlayers = 0;


	PLAYER_VECTOR::iterator theIterator;



	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		if( next->GetPlayerState() == PLAYER_STATE_ALIVE )
		{
			nummberOfAlivePlayers++;
		}

	}

	return nummberOfAlivePlayers;


}



Player * ComputerController::ChooseNextEnemy()
{

	if( GetNumberOfAlivePlayers() > 1)
	{
		int numberOfPlayers =  (int)Universe::GetPlayers().size();
		bool done = false;
		while(!done)
		{
		int possibleTargetIndex = rand()%numberOfPlayers;
		Player * possibleTarget = Universe::GetPlayers()[possibleTargetIndex];
		if(  
			(possibleTarget != this->myPlayer) &&
			possibleTarget->GetPlayerState() == PLAYER_STATE_ALIVE
			)
			return possibleTarget;
		}

	}

	return 0;

}



int ComputerController::GetControlEvent()
{
	int controlEvent = CONTROL_EVENT_DO_NOTHING;

	return controlEvent;

}



bool ComputerController::IsDropBombPressed()
{
	return false;
}

void ComputerController::DrawBoundingBox( _asNode * asNode )
{
	// Comment in code below to see A* information in each block

// 	int targetX = asNode->x * MAP_BLOCK_WIDTH + Universe::GetMapLeftX();
// 	int targetY = asNode->y * MAP_BLOCK_HEIGHT + Universe::GetMapTopY();
// 
// 
// 	int pitch;
// 	UCHAR * surface;
// 	surface = DDraw_Lock_Surface(lpddsback, &pitch);
// 
// 	int color = 211; // yellow
// 
// 
// 	int alpha = 0;
// 	int red = 255;
// 	int green = 0;
// 	int blue = 0;
// 
// 	RECT boundingBox;
// 
// 	boundingBox.left = targetX;
// 	boundingBox.right = targetX + 32;
// 	boundingBox.top = targetY;
// 	boundingBox.bottom = targetY + 32;
// 
// 	// top line
// 	HLine32(boundingBox.left, boundingBox.right, boundingBox.top, alpha, red, green, blue, surface, pitch );
// 
// 	//// bottom line
// 	HLine32(boundingBox.left, boundingBox.right, boundingBox.bottom, alpha, red, green, blue, surface, pitch );
// 
// 	//// right line
// 	VLine32(boundingBox.top, boundingBox.bottom, boundingBox.right, alpha, red, green, blue, surface, pitch);
// 
// 	//// left line
// 	VLine32(boundingBox.top, boundingBox.bottom, boundingBox.left, alpha, red, green, blue, surface, pitch);
// 
// 
// 	//Draw_Text_GDI( "50", 64, 50, 160, "Times New Roman", 65, lpddsback);
// 
// 	string fString;
// 	string gString;
// 	string hString;
// 
// 	stringstream fout;
// 	stringstream gout;
// 	stringstream hout;
// 
// 	fout << asNode->f;
// 	fString = fout.str();
// 
// 	gout << asNode->g;
// 	gString = gout.str();
// 
// 	hout << asNode->h;
// 	hString = hout.str();
// 
// 
// 
// 	Draw_Text_GDI( fString.c_str(), targetX + 2, targetY + 2, 160, "Times New Roman", 65, lpddsback);
// 	Draw_Text_GDI( gString.c_str(), targetX + 2, targetY + 15, 160, "Times New Roman", 65, lpddsback);
// 	Draw_Text_GDI( hString.c_str(), targetX + 20, targetY + 15, 160, "Times New Roman", 65, lpddsback);
// 
// 
// 	DDraw_Unlock_Surface(lpddsback);
}





