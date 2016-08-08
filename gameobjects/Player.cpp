#include "Player.h"


#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"

#include "SimpleGameObject.h"
#include "Number.h"
// #include "../input/Keyboard.h"
// #include "../input/Joystick.h"
#include "../input/Controller.h"

#include "../sound/MSound.h"

#include "ControlEvent.h"


#include <iostream>
#include <sstream>
using namespace std;


#define EAST         0
#define NORTH        1
#define WEST         2
#define SOUTH        3




void Player::HandleMoveDown()
{

	GameObject * blockingGameObjectBelowAndRight = this->GetBlockingGameObjectImmediatelyBelowAndToTheRight();
	GameObject * blockingGameObjectBelowAndLeft = this->GetBlockingGameObjectImmediatelyBelowAndToTheLeft();

	if( blockingGameObjectBelowAndRight && blockingGameObjectBelowAndLeft)
	{
		HandleBlockedMoveDown();
	}
	else 
	if( !blockingGameObjectBelowAndRight && ! blockingGameObjectBelowAndLeft)
	{
		HandleMoveDownWithNoBlockBelow();
	}
	else
	if( blockingGameObjectBelowAndRight)
	{
		HandleMoveDownWithBlockBelow((Block *)blockingGameObjectBelowAndRight);
	}
	else
	{
		HandleMoveDownWithBlockBelow((Block *)blockingGameObjectBelowAndLeft);
	}

}


void Player::HandleMoveDownWithBlockBelow(Block * aBlock)
{
	int playerX = this->GetBlitterObject()->GetX();
	RECT collisionBox = this->GetCollisionBox();


	if( PlayerLeftEdgeOverlapsWithRightHalfOfBlock(aBlock))
	{
		// Case 1
		HandleMoveDownLeftEdgeOverRightHalf();
	}
	else
	if( PlayerLeftEdgeOverlapsWithLeftHalfOfBlock(aBlock))
	{
		// Cases 2 and 3
		HandleMoveUpOrDownLeftEdgeOverLeftHalf();
	}
	else
	if( PlayerDirectlyAboveOrBelowBlock(aBlock))
	{
		// Case 4
		HandleBlockedMoveDown();
	}
	else
	if( PlayerRightEdgeOverlapsWithRightHalfOfBlock(aBlock))
	{
		// Cases 5 and 6
		HandleMoveUpOrDownRightEdgeOverRightHalf();
	}
	else
	if( PlayerRightEdgeOverlapsWithLeftHalfOfBlock(aBlock))
	{
		// Case 7
		HandleMoveDownRightEdgeOverLeftHalf();
	}


}

Number * Player::GetScoreNumber()
{
	scoreNumber->SetValue(this->GetNumberOfWins());
	scoreNumber->GetBlitterObject()->Animate();
	return scoreNumber;
}


bool Player::PlayerLeftEdgeOverlapsWithRightHalfOfBlock(Block * aBlock)
{
	bool isLeftEdgeOverRightHalfOfBlock = false;

	int blockWidth= aBlock->GetBlitterObject()->GetWidth();
	int halfWidth = blockWidth / 2;
	int blockLeftX = aBlock->GetCollisionBox().left;

	int blockRightX = aBlock->GetCollisionBox().right;
	int blockMiddleX = blockRightX - ( halfWidth - 1);

	int playerLeft = this->GetCollisionBox().left;

	if(  (playerLeft >= blockMiddleX) &&
		 (playerLeft <= blockRightX)
		)
	{

	isLeftEdgeOverRightHalfOfBlock = true;

	}

	return isLeftEdgeOverRightHalfOfBlock;

}

bool Player::PlayerBottomEdgeOverlapsWithTopHalfOfBlock(Block * aBlock)
{
	bool isPlayerBottomEdgeOverlapsWithTopHalfOfBlock = false;

	int blockHeight= aBlock->GetBlitterObject()->GetWidth();
	int halfHeight = blockHeight / 2;
	int blockTopY = aBlock->GetCollisionBox().top;

	int blockBottomY = aBlock->GetCollisionBox().bottom;
	int blockMiddleY = blockBottomY - ( halfHeight - 1);

	int playerBottom = this->GetCollisionBox().bottom;

	if(  (playerBottom <= blockMiddleY) &&
		(playerBottom >= blockTopY)
		)
	{
		isPlayerBottomEdgeOverlapsWithTopHalfOfBlock = true;
	}

	return isPlayerBottomEdgeOverlapsWithTopHalfOfBlock;
}

bool Player::PlayerBottomEdgeOverlapsWithBottomHalfOfBlock(Block * aBlock)
{
	bool isOverlapping = false;

	int blockHeight= aBlock->GetBlitterObject()->GetWidth();
	int halfHeight = blockHeight / 2;

	int blockBottomY = aBlock->GetCollisionBox().bottom;
	int blockMiddleY = blockBottomY - ( halfHeight - 1);

	int playerBottom = this->GetCollisionBox().bottom;

	if(  (playerBottom <= blockBottomY) &&
		(playerBottom >= blockMiddleY)
		)
	{
		isOverlapping = true;
	}

	return isOverlapping;
}



bool Player::PlayerTopEdgeOverlapsWithTopHalfOfBlock(Block * aBlock)
{
	bool isOverlapping = false;

	int blockHeight= aBlock->GetBlitterObject()->GetWidth();
	int halfHeight = blockHeight / 2;

	int blockBottomY = aBlock->GetCollisionBox().bottom;

	int blockTop = aBlock->GetCollisionBox().top;
	int blockMiddleY = blockBottomY - ( halfHeight - 1);

	int playerTop = this->GetCollisionBox().top;

	if(  (playerTop <= blockMiddleY) &&
		(playerTop >= blockTop)
		)
	{
		isOverlapping = true;
	}

	return isOverlapping;
}


bool Player::PlayerTopEdgeOverlapsWithBottomHalfOfBlock(Block * aBlock)
{
	bool isOverlapping = false;

	int blockHeight= aBlock->GetBlitterObject()->GetWidth();
	int halfHeight = blockHeight / 2;

	int blockBottomY = aBlock->GetCollisionBox().bottom;

	int blockTop = aBlock->GetCollisionBox().top;
	int blockMiddleY = blockBottomY - ( halfHeight - 1);

	int playerTop = this->GetCollisionBox().top;

	if(  (playerTop <= blockBottomY) &&
		(playerTop >= blockMiddleY)
		)
	{
		isOverlapping = true;
	}

	return isOverlapping;
}





bool Player::PlayerRightEdgeOverlapsWithLeftHalfOfBlock(Block * aBlock)
{
	bool isRightEdgeOverLeftHalfOfBlock = false;

	int blockWidth= aBlock->GetBlitterObject()->GetWidth();
	int halfWidth = blockWidth / 2;
	int blockLeftX = aBlock->GetCollisionBox().left;

	int blockRightX = aBlock->GetCollisionBox().right;
	int blockMiddleX = blockLeftX + ( halfWidth - 1);

	int playerRight = this->GetCollisionBox().right;

	if(  (playerRight <= blockMiddleX) &&
		(playerRight >= blockLeftX)
		)
	{

		isRightEdgeOverLeftHalfOfBlock = true;

	}

	return isRightEdgeOverLeftHalfOfBlock;

}


bool Player::PlayerDirectlyAboveOrBelowBlock(Block * aBlock)
{
	bool isPlayerDirectlyAboveOrBelowBlock = false;
 	int blockRightX = aBlock->GetCollisionBox().right;
 
 	int playerRight = this->GetCollisionBox().right;

	if(  playerRight == blockRightX )
	{
		isPlayerDirectlyAboveOrBelowBlock = true;
	}

	return isPlayerDirectlyAboveOrBelowBlock;
}


bool Player::PlayerDirectlyToLeftOrRightOfBlock(Block * aBlock)
{
	bool isAligned = false;
	int blockTopX = aBlock->GetCollisionBox().top;

	int playerTop = this->GetCollisionBox().top;

	if(  playerTop == blockTopX )
	{
		isAligned = true;
	}

	return isAligned;
}



bool Player::PlayerLeftEdgeOverlapsWithLeftHalfOfBlock(Block * aBlock)
{
	bool isLeftEdgeOverLeftHalfOfBlock = false;

	int blockWidth= aBlock->GetBlitterObject()->GetWidth();
	int halfWidth = blockWidth / 2;
	int blockLeftX = aBlock->GetCollisionBox().left;

	int blockRightX = aBlock->GetCollisionBox().right;
	int blockMiddleX = blockLeftX + ( halfWidth - 1);

	int playerLeft = this->GetCollisionBox().left;

	if(  (playerLeft <= blockMiddleX) &&
		(playerLeft > blockLeftX)
		)
	{
		isLeftEdgeOverLeftHalfOfBlock = true;
	}

	return isLeftEdgeOverLeftHalfOfBlock;

}





bool Player::PlayerRightEdgeOverlapsWithRightHalfOfBlock(Block * aBlock)
{
	bool isRightEdgeOverRightHalfOfBlock = false;

	int blockMiddleX = aBlock->GetCollisionBoxMiddleX();
	int blockRightX = aBlock->GetCollisionBox().right;

	int playerRight = this->GetCollisionBox().right;

	if(  (playerRight > blockMiddleX) &&
		(playerRight <= blockRightX)
		)
	{
		isRightEdgeOverRightHalfOfBlock = true;
	}

	return isRightEdgeOverRightHalfOfBlock;
}







void Player::HandleMoveDownLeftEdgeOverRightHalf()
{
	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
	{
		this->GetBlitterObject()->Set_Animation(SOUTH);
	}
}


void Player::HandleMoveRightBottomEdgeOverlapsTopHalf()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != EAST)
	{
		this->GetBlitterObject()->Set_Animation(EAST);
	}
}


void Player::HandleMoveLeftBottomEdgeOverlapsTopHalf()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
	{
		this->GetBlitterObject()->Set_Animation(WEST);
	}
}




void Player::HandleMoveUpOrDownLeftEdgeOverLeftHalf()
{
	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();

	if(currentDirection == WEST)
	{
		this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	}
	else
	if( currentDirection == EAST)
	{
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	}
}





void Player::HandleMoveRightOrLeftWithBottomEdgeOverlappingBottomeHalf()
{
	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();

	if(currentDirection == SOUTH)
	{
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	}
	else
	if( currentDirection == NORTH)
	{
		this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	}
}





void Player::HandleMoveDownRightEdgeOverLeftHalf()
{
	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
	{
		this->GetBlitterObject()->Set_Animation(SOUTH);
	}
}



void Player::HandleMoveUpPlayerRightEdgeOverlapsLeftHalf()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
	{
		this->GetBlitterObject()->Set_Animation(NORTH);
	}
}




void Player::HandleBlockedMoveDown()
{
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
	{
		this->GetBlitterObject()->Set_Animation(SOUTH);
	}
	this->GetBlitterObject()->Animate();
}


void Player::HandleBlockedMoveRight()
{
	if (this->GetBlitterObject()->Get_Current_Animation() != EAST)
	{
		this->GetBlitterObject()->Set_Animation(EAST);
	}
	this->GetBlitterObject()->Animate();
}


void Player::HandleBlockedMoveLeft()
{
	if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
	{
		this->GetBlitterObject()->Set_Animation(WEST);
	}
	this->GetBlitterObject()->Animate();
}






void Player::HandleBlockedMoveUp()
{
	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
	{
		this->GetBlitterObject()->Set_Animation(NORTH);
	}
	this->GetBlitterObject()->Animate();
}



 



void Player::HandleMoveUpOrDownRightEdgeOverRightHalf()
{
	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();

	if(currentDirection == WEST)
	{
		this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	}
	else
	if( currentDirection == EAST)
	{
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	}
}





void Player::HandleMoveRightOrLeftTopEdgeOverlappingTopHalf()
{
	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();



	if(currentDirection == NORTH)
	{
		this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	}
	else
	if( currentDirection == SOUTH)
	{
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	}
}


void Player::HandleMoveRightTopEdgeOverlappingBottomHalf()
{

	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);

	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();
	if(currentDirection != EAST)
	{
		this->GetBlitterObject()->Set_Animation(EAST);
	}

	this->GetBlitterObject()->Animate();
}


void Player::HandleMoveLeftTopEdgeOverlappingBottomHalf()
{
	int currentDirection = this->GetBlitterObject()->Get_Current_Animation();


	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);

	if(currentDirection != WEST)
	{
		this->GetBlitterObject()->Set_Animation(WEST);
	}
	this->GetBlitterObject()->Animate();
}






void Player::HandleMoveDownWithNoBlockBelow()
{
	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
		this->GetBlitterObject()->Set_Animation(SOUTH);
	this->GetBlitterObject()->Animate();
}

void Player::HandleMoveUpWithNoBlockAbove()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
		this->GetBlitterObject()->Set_Animation(NORTH);
	this->GetBlitterObject()->Animate();
}



void Player::HandleMoveUpWithBlockAbove(Block * aBlock)
{
	int playerX = this->GetBlitterObject()->GetX();
	RECT collisionBox = this->GetCollisionBox();


	if( PlayerLeftEdgeOverlapsWithRightHalfOfBlock(aBlock))
	{
		// Case 1
		HandleMoveUpPlayerLeftEdgeOverlapsBlockRightHalf();
	}
	else
	if( PlayerLeftEdgeOverlapsWithLeftHalfOfBlock(aBlock))
	{
		// Cases 2 and 3
		HandleMoveUpOrDownLeftEdgeOverLeftHalf();
	}
	else
	if( PlayerDirectlyAboveOrBelowBlock(aBlock))
	{
		// Case 4
		HandleBlockedMoveUp();
	}
	else
	if( PlayerRightEdgeOverlapsWithRightHalfOfBlock(aBlock))
	{
		// Cases 5 and 6
		HandleMoveUpOrDownRightEdgeOverRightHalf();
	}
	else
	if( PlayerRightEdgeOverlapsWithLeftHalfOfBlock(aBlock))
	{
		// Case 7
		HandleMoveUpPlayerRightEdgeOverlapsLeftHalf();
	}


}



void Player::HandleMoveUpPlayerLeftEdgeOverlapsBlockRightHalf()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
	{
		this->GetBlitterObject()->Set_Animation(NORTH);
	}
}




void Player::HandleMoveRightWithNoBlockToTheRight()
{
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != EAST)
		this->GetBlitterObject()->Set_Animation(EAST);
	this->GetBlitterObject()->Animate();
}


bool Player::HandleMoveRightWithBlockToTheRight(Block * aBlock)
{
	bool playerMoved = TRUE;

	int playerX = this->GetBlitterObject()->GetX();
	RECT collisionBox = this->GetCollisionBox();


	if( PlayerBottomEdgeOverlapsWithTopHalfOfBlock(aBlock))
	{
		// Case 1
		HandleMoveRightBottomEdgeOverlapsTopHalf();
	}
	else
	if( PlayerDirectlyToLeftOrRightOfBlock(aBlock))
	{
		// Case 4
		HandleBlockedMoveRight();
		playerMoved = FALSE;
	}
	else
	if( PlayerBottomEdgeOverlapsWithBottomHalfOfBlock(aBlock))
	{
		// Cases 2 and 3
		HandleMoveRightOrLeftWithBottomEdgeOverlappingBottomeHalf();
	}
	else
	if( PlayerTopEdgeOverlapsWithTopHalfOfBlock(aBlock) )
	{
		// Cases 5 and 6
		HandleMoveRightOrLeftTopEdgeOverlappingTopHalf();

	}
	else
	if( PlayerTopEdgeOverlapsWithBottomHalfOfBlock(aBlock))
	{
		// Case 7
		HandleMoveRightTopEdgeOverlappingBottomHalf();
	}

	return playerMoved;

}



bool Player::HandleMoveLeftWithBlockToTheLeft(Block * aBlock)
{
	bool playerMoved = TRUE;

	int playerX = this->GetBlitterObject()->GetX();
	RECT collisionBox = this->GetCollisionBox();


	if( PlayerBottomEdgeOverlapsWithTopHalfOfBlock(aBlock))
	{
		// Case 1
		HandleMoveLeftBottomEdgeOverlapsTopHalf();
	}
	else
	if( PlayerDirectlyToLeftOrRightOfBlock(aBlock))
	{
		// Case 4
		HandleBlockedMoveLeft();
		playerMoved = FALSE;
	}
	else
	if( PlayerBottomEdgeOverlapsWithBottomHalfOfBlock(aBlock))
	{
		// Cases 2 and 3
		HandleMoveRightOrLeftWithBottomEdgeOverlappingBottomeHalf();
 	}
	else
	if( PlayerTopEdgeOverlapsWithTopHalfOfBlock(aBlock) )
	{
		// Cases 5 and 6
		HandleMoveRightOrLeftTopEdgeOverlappingTopHalf();
	}
	else
	if( PlayerTopEdgeOverlapsWithBottomHalfOfBlock(aBlock))
	{
		// Case 7
		HandleMoveLeftTopEdgeOverlappingBottomHalf();
	}
	return playerMoved;

}









void Player::HandleMoveLeftWithNoBlockToTheLeft()
{
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
		this->GetBlitterObject()->Set_Animation(WEST);
	this->GetBlitterObject()->Animate();
}






bool Player::IsCollisionWithBomb()
{

	BOB * playerBOB = this->GetTheCollisionBob();

	Bomb * foundBomb = 0;
	BOMB_VECTOR::iterator theBombIterator;

	BOMB_VECTOR & theBombs = Universe::GetBombs();

	for(	theBombIterator = theBombs.begin();
		theBombIterator != theBombs.end();
		theBombIterator++
		)
	{
		Bomb * nextBomb = *theBombIterator;
		BOB * bombBOB = nextBomb->GetBlitterObject()->getTheBOB();
		boolean collision = Collision_BOBS(playerBOB,bombBOB);

		if(collision)
		{
			return TRUE;
		}

	}

	return FALSE;


}


int Collision_BOBS_Half_Overlap(BOB_PTR bob1, BOB_PTR bob2)
{
	// are these a valid bobs
	if (!bob1 || !bob2)
		return(0);

	// get the radi of each rect
	int width1  = (bob1->width>>1);
	int height1 = (bob1->height>>1);

	int width2  = (bob2->width>>1);
	int height2 = (bob2->height>>1);



	// compute center of each rect
	int cx1 = bob1->x + width1;
	int cy1 = bob1->y + height1;

	int cx2 = bob2->x + width2;
	int cy2 = bob2->y + height2;

	// compute deltas
	int dx = abs(cx2 - cx1);
	int dy = abs(cy2 - cy1);

	// test if rects overlap
	if (dx < ( (width1+width2) / 2) && dy < ((height1+height2)/2))
		return(1);
	else
		// else no collision
		return(0);

} // end Collision_BOBS



Powerup *  Player::IsCollisionWithPowerup()
{
	BOB * playerBOB = this->GetTheCollisionBob();
	POWERUP_VECTOR::iterator theIterator;
	POWERUP_VECTOR & theBombs = Universe::GetPowerups();

	for(	theIterator = theBombs.begin();
		theIterator != theBombs.end();
		theIterator++
		)
	{
		Powerup * next = *theIterator;
		BOB * nextBOB = next->GetBlitterObject()->getTheBOB();
		boolean collision = Collision_BOBS_Half_Overlap(playerBOB,nextBOB);

		if(collision)
		{
			return next;
		}

	}
	return 0;
}


// FlamePowerup *  Player::IsCollisionWithFlamePowerup()
// {
// 	BOB * playerBOB = this->GetTheCollisionBob();
// 	FLAME_POWERUP_VECTOR::iterator theIterator;
// 	FLAME_POWERUP_VECTOR & theFlames = Universe::GetFlamePowerups();
// 
// 	for(	theIterator = theFlames.begin();
// 		theIterator != theFlames.end();
// 		theIterator++
// 		)
// 	{
// 		FlamePowerup * next = *theIterator;
// 		BOB * nextBOB = next->GetBlitterObject()->getTheBOB();
// 		boolean collision = Collision_BOBS_Half_Overlap(playerBOB,nextBOB);
// 
// 		if(collision)
// 		{
// 			return next;
// 		}
// 
// 	}
// 	return 0;
// }




void Player::HandleMoveUp()
{

	GameObject * blockingGameObjectAboveAndRight = this->GetBlockingGameObjectImmediatelyAboveAndToTheRight();
	GameObject * blockingGameObjectAboveAndLeft = this->GetBlockingGameObjectImmediatelyAboveAndToTheLeft();


	if( blockingGameObjectAboveAndRight && blockingGameObjectAboveAndLeft)
	{
		HandleBlockedMoveUp();
	}
	else
	if( !blockingGameObjectAboveAndRight && !blockingGameObjectAboveAndLeft)
	{
		HandleMoveUpWithNoBlockAbove();
	}
	else
	if(blockingGameObjectAboveAndRight)
	{
		HandleMoveUpWithBlockAbove((Block *)blockingGameObjectAboveAndRight);
	}
	else
	{
		HandleMoveUpWithBlockAbove((Block *)blockingGameObjectAboveAndLeft);
	}
}


bool Player::HandleMoveRight(int controlEvent)
{

	bool playerMoved = TRUE;

	GameObject * blockingGameObjectRightAndAbove = this->GetBlockingGameObjectImmediatelyToTheRightAndAbove();
	GameObject * blockingGameObjectRightAndBelow = this->GetBlockingGameObjectImmediatelyToTheRightAndBelow();

	if( blockingGameObjectRightAndAbove && blockingGameObjectRightAndBelow)
	if(controlEvent == CONTROL_EVENT_MOVE_SOUTH_EAST)
	{
		HandleMoveDown();
	}
	else
	if(controlEvent == CONTROL_EVENT_MOVE_NORTH_EAST)
	{
		HandleMoveUp();
	}
	else
	{
		HandleBlockedMoveRight();
		playerMoved = FALSE;
	}
	else
	if( !blockingGameObjectRightAndAbove && !blockingGameObjectRightAndBelow)
	{
		HandleMoveRightWithNoBlockToTheRight();
	}
	else
	if(blockingGameObjectRightAndAbove)
	{
		HandleMoveRightWithBlockToTheRight((Block *)blockingGameObjectRightAndAbove);
	}
	else
	{
		HandleMoveRightWithBlockToTheRight((Block *)blockingGameObjectRightAndBelow);
	}
	return playerMoved;


}



void Player::HandleMoveLeft(int controlEvent)
{

	GameObject * blockingGameObjectLeftAndAbove = this->GetBlockingGameObjectImmediatelyToTheLeftAndAbove();
	GameObject * blockingGameObjectLeftAndBelow = this->GetBlockingGameObjectImmediatelyToTheLeftAndBelow();

	if( blockingGameObjectLeftAndAbove && blockingGameObjectLeftAndBelow)
	{
		if(controlEvent == CONTROL_EVENT_MOVE_SOUTH_WEST)
		{
			HandleMoveDown();
		}
		else
		if(controlEvent == CONTROL_EVENT_MOVE_NORTH_WEST)
		{
			HandleMoveUp();
		}
		else
		{
			HandleBlockedMoveLeft();
		}

	}
	else
	if( !blockingGameObjectLeftAndAbove && !blockingGameObjectLeftAndBelow)
	{
		HandleMoveLeftWithNoBlockToTheLeft();
	}
	else
	if(blockingGameObjectLeftAndAbove)
	{
		HandleMoveLeftWithBlockToTheLeft((Block *)blockingGameObjectLeftAndAbove);
	}
	else
	{
		HandleMoveLeftWithBlockToTheLeft((Block *)blockingGameObjectLeftAndBelow);
	}



}



GameObject *  Player::GetBlockingGameObjectImmediatelyToTheLeftAndAbove()
{
	GameObject * foundGameObject = 0;

	int playerLeft = this->GetCollisionBox().left;
	int playerTop = this->GetCollisionBox().top;

	foundGameObject = Universe::GetBlockAtPoint(playerLeft - 1, playerTop);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerLeft - 1, playerTop);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}



GameObject *  Player::GetBlockingGameObjectImmediatelyBelowAndToTheRight()
{
	GameObject * foundGameObject = 0;

	int playerRight = this->GetCollisionBox().right;
	int playerBottom = this->GetCollisionBox().bottom;

	foundGameObject = Universe::GetBlockAtPoint(playerRight, playerBottom + 1);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerRight, playerBottom + 1);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}


GameObject *  Player::GetBlockingGameObjectImmediatelyAboveAndToTheRight()
{
	GameObject * foundGameObject = 0;

	int playerRight = this->GetCollisionBox().right;
	int playerTop = this->GetCollisionBox().top;

	foundGameObject = Universe::GetBlockAtPoint(playerRight, playerTop - 1);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerRight, playerTop - 1);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}




GameObject *  Player::GetBlockingGameObjectImmediatelyBelowAndToTheLeft()
{
	GameObject * foundGameObject = 0;

	int playerLeft = this->GetCollisionBox().left;
	int playerBottom = this->GetCollisionBox().bottom;

	foundGameObject = Universe::GetBlockAtPoint(playerLeft, playerBottom + 1);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerLeft, playerBottom + 1);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}


GameObject *  Player::GetBlockingGameObjectImmediatelyAboveAndToTheLeft()
{
	GameObject * foundGameObject = 0;

	int playerLeft = this->GetCollisionBox().left;
	int playerTop = this->GetCollisionBox().top;

	foundGameObject = Universe::GetBlockAtPoint(playerLeft, playerTop - 1);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerLeft, playerTop - 1);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}



GameObject *  Player::GetBlockingGameObjectImmediatelyToTheRightAndAbove()
{
	GameObject * foundGameObject = 0;

	int playerRight = this->GetCollisionBox().right;
	int playerTop = this->GetCollisionBox().top;

	foundGameObject = Universe::GetBlockAtPoint(playerRight + 1, playerTop);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerRight + 1, playerTop);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}




GameObject *  Player::GetBlockingGameObjectImmediatelyToTheLeftAndBelow()
{
	GameObject * foundGameObject = 0;

	int playerLeft = this->GetCollisionBox().left;
	int playerBottom = this->GetCollisionBox().bottom;

	foundGameObject = Universe::GetBlockAtPoint(playerLeft - 1, playerBottom);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerLeft - 1, playerBottom);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}


GameObject *  Player::GetBlockingGameObjectImmediatelyToTheRightAndBelow()
{
	GameObject * foundGameObject = 0;

	int playerRight = this->GetCollisionBox().right;
	int playerBottom = this->GetCollisionBox().bottom;

	foundGameObject = Universe::GetBlockAtPoint(playerRight + 1, playerBottom);

	if(!foundGameObject)
	{
		Bomb * foundBomb = Universe::GetBombAtPoint(playerRight + 1, playerBottom);
		if(foundBomb && !foundBomb->IsPlayerMovingOverAfterDropping(this))
		{
			foundGameObject = foundBomb;
		}

	}

	return foundGameObject;

}




bool Player::Update()
{

	int controlEvent = CONTROL_EVENT_DO_NOTHING;
	bool playerMoved = FALSE;

	controlEvent = this->theController->GetControlEvent();
	this->Update(controlEvent);


	if (this->theController->IsDropBombPressed())
	{
		int x = 3;
		if( 
			(bombDropCoundownTimer <= 0) &&
			!IsCollisionWithBomb() && 
			(numAllowedBombs > numBombsDropped)
		  )
		{
			this->numBombsDropped++;
			controlEvent = CONTROL_EVENT_DROP_BOMB;
			this->Update(controlEvent);
			bombDropCoundownTimer = bombDropCoundownTimerInitialValue;

		}
	}

	if(bombDropCoundownTimer > 0)
	{
		bombDropCoundownTimer--;
	}


	Powerup * aPowerup = IsCollisionWithPowerup();
	if(aPowerup)
	{
		aPowerup->Activate(this);
		Universe::RemovePowerup(aPowerup );
		delete aPowerup;
		Sound::PlaySound(Sound::pickup_powerup_sound);
	}



	bool collisionWithExplosion = ExplosionPart::IsGameObjectInAnyExplosionPart(this);
	if(collisionWithExplosion)
	{
		this->playerState = PLAYER_STATE_DEAD;
		Sound::PlaySound(Sound::player_dies_sound);
	}
	return collisionWithExplosion;

}



void Player::Update(int controlEvent)
{

	switch(controlEvent)
	{

	case CONTROL_EVENT_MOVE_EAST:
	case CONTROL_EVENT_MOVE_SOUTH_EAST:
	case CONTROL_EVENT_MOVE_NORTH_EAST:
		HandleMoveRight(controlEvent);
		break;

	case CONTROL_EVENT_MOVE_SOUTH_WEST:
	case CONTROL_EVENT_MOVE_WEST:
	case CONTROL_EVENT_MOVE_NORTH_WEST:
		HandleMoveLeft(controlEvent);
		break;

	case CONTROL_EVENT_MOVE_SOUTH:
		HandleMoveDown();
		break;

	case CONTROL_EVENT_MOVE_NORTH:
		HandleMoveUp();
		break;

	case CONTROL_EVENT_DROP_BOMB:
		HandleDropBomb();
		break;
	}


	
}




RECT Player::GetRoundedPlayerLocationMapSquare()
{
	RECT theRect;

	int playerX = this->GetCollisionBox().left;
	int playerY = this->GetCollisionBox().top;

	playerX += MAP_BLOCK_WIDTH / 2;
	playerY += MAP_BLOCK_HEIGHT / 2;

	int blockHorizontalOffset = playerX / MAP_BLOCK_WIDTH;
	int blockVerticalOffset = playerY/ MAP_BLOCK_HEIGHT;
	theRect.left = blockHorizontalOffset * MAP_BLOCK_WIDTH;
	theRect.right = theRect.left + MAP_BLOCK_WIDTH;

	theRect.top = blockVerticalOffset * MAP_BLOCK_HEIGHT;
	theRect.bottom = theRect.top + MAP_BLOCK_HEIGHT;

	return theRect;

}


void Player::HandleDropBomb()
{
	RECT roundedLocation = GetRoundedPlayerLocationMapSquare();
	int bombX = roundedLocation.left;
	int bombY = roundedLocation.top;

	Bomb * aBomb = new Bomb(bombX, bombY,this );
	Universe::GetBombs().push_back(aBomb);

	Sound::PlaySound(Sound::drop_bomb_sound, 100);

}


int Player::GetRoundedSquareCenterX()
{
	RECT roundedLocation = this->GetRoundedPlayerLocationMapSquare();

	int x = roundedLocation.left + 16;

	return x;

}


int Player::GetRoundedSquareCenterY()
{
	RECT roundedLocation = this->GetRoundedPlayerLocationMapSquare();

	int y = roundedLocation.top + 16;

	return y;


}



int Player::GetCollisionBoxCenterX() 
{

	RECT collisionBox = this->GetCollisionBox();

	int x = collisionBox.left + 16;

	return x;

}


int Player::GetCollisionBoxCenterY() 
{

	RECT collisionBox = this->GetCollisionBox();

	int y = collisionBox.top + 16;

	return y;

}



RECT Player::GetCollisionBox()
{
	int playerX = theBlitterObject_->GetX();
	int playerY = theBlitterObject_->GetY();
	int playerWidth = theBlitterObject_->GetWidth();
	int playerHeight= theBlitterObject_->GetHeight();

	RECT collisionBox;

	collisionBox.top = playerY + 12;
	collisionBox.left = playerX + 6;
	collisionBox.bottom = collisionBox.top + 32 - 1;
	collisionBox.right = collisionBox.left + 32 -1;

	return collisionBox;
}




void Player::Draw(LPDIRECTDRAWSURFACE7 dest)
{

	theBlitterObject_->Draw(dest);

	int drawBoundingBox = 0;

	if(drawBoundingBox)
	{
		this->DrawCollisionBox(dest);
	}
}


string Player::GetNameFromPlayerType()
{
	int aPlayerType = this->GetPlayerType();
	switch(aPlayerType)
	{
	case WHITE_PLAYER:
		return "White";
		break;
	case BLACK_PLAYER:
		return "Black";
		break;
	case RED_PLAYER:
		return "Red";
		break;
	case BLUE_PLAYER:
		return "Blue";
		break;

	}
	return "";
}


string Player::GetBitmapFilenameFromPlayerType(int aPlayerType)
{

 	return  GetNameFromPlayerType() + string("Player.bmp");
}

void Player::PlaceExplodingPlayer()
{
	int explodingPlayerX = GetCollisionBox().left;
	int explodingPlayerY = GetCollisionBox().top;
	ExplodingPlayer * newExplodingPlayer = new ExplodingPlayer( explodingPlayerX, explodingPlayerY, playerType );
	Universe::GetExplodingPlayers().push_back(newExplodingPlayer);

}


#define NUM_FRAMES_PER_ANIMATION 4
#define NUM_ANIMATIONS 4



void Player::SetInitialValuesForNewMatch()
{
	numberOfWins = 0;
}

void Player::SetInitialValuesForNewRound()
{
	playerState = PLAYER_STATE_ALIVE;

	this->numAllowedBombs = 1;
	this->numBombsDropped = 0;
	this->explosionSize = 2;
	this->GetBlitterObject()->Set_Pos(initialX, initialY);

	theBlitterObject_->Set_Animation(SOUTH);

	BOB * bob = theBlitterObject_->getTheBOB();
	bob->curr_frame = bob->animations[bob->curr_animation][bob->anim_index];

}


Player::Player()
{

	theBlitterObject_ = 0;
}

Player::Player(int x, int y, int aPlayerType)
{

	x -= 6;
	y -= 12;



	initialX = x;
	initialY = y;

	playerType = aPlayerType;
	name = 	GetNameFromPlayerType();
	moveIncrementAmount = 2;
	playerState = PLAYER_STATE_ALIVE;
	numberOfWins = 0;

	int playerWidth = 44;
	int playerHeight = 44;

	int totalNumFrames = 12;
	int transparentColorKey = RGB(0,107,0);

	bombDropCoundownTimerInitialValue = 20;
	bombDropCoundownTimer = 0;

	explosionSize = 6;

	theBlitterObject_ = new BlitterObject(x,y,playerWidth,playerHeight,totalNumFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);

	int animations[NUM_ANIMATIONS][NUM_FRAMES_PER_ANIMATION] =
	{
			{0,1,0,2},
			{3,4,3,5},
			{6,7,6,8},
			{9,10,9,11}
	 };


	string shortFileName = GetBitmapFilenameFromPlayerType(playerType);
	

//	string pathPrefix = "../bitmaps/";
	string pathPrefix = "";
//	string longFilename = pathPrefix.operator +=(shortFileName);
	string longFilename = pathPrefix + shortFileName;

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, longFilename.c_str(), 0, 0 );

	int frameNumber = 0;
	for(int row = 0; row < 4; row++)
	{ 
		for(int column = 0; column < 3; column++)
		{
		theBlitterObject_->Load_Frame(dds,frameNumber,column, row,BITMAP_EXTRACT_MODE_CELL);  
		frameNumber++;
		}

	}


	Unload_Bitmap_File(&bitmap8bit);

	// set the animation sequences

	for(int animation = 0; animation < 4; animation++)
	{
		theBlitterObject_->Load_Animation(animation,NUM_FRAMES_PER_ANIMATION, animations[animation]);
	}


	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);

	this->numAllowedBombs = 2;
	this->numBombsDropped = 0;


	theCollisionBOB_  = new BOB();

	string playerTypeName = GetNameFromPlayerType();

	string iconLongFilename = pathPrefix + string("bitmaps/InGame/Scoreboard/" ) + playerTypeName + string("Icon.bmp");
	scoreIcon = new SimpleGameObject(0,0,36,30,iconLongFilename,_RGB32BIT(0,0,182,0));
	string iconCryLongFilename = pathPrefix + string("bitmaps/InGame/Scoreboard/" ) + playerTypeName + string("CryIcon.bmp");
	scoreCryIcon = new SimpleGameObject(0,0,36,30,iconCryLongFilename,_RGB32BIT(0,0,182,0));

	
	scoreShell = new SimpleGameObject(1,1, 18,18,"bitmaps/InGame/Scoreboard/BlankPlayerScore.bmp",1);
	scoreNumber = new Number(1,1);
	scoreNumber->SetValue(this->GetNumberOfWins());



}



SimpleGameObject * Player::GetScoreIcon()
{
	if(this->GetPlayerState() == PLAYER_STATE_ALIVE)
	{
		return scoreIcon;
	}
	else
	{
		return scoreCryIcon;
	}

}

void Player::SetScoreIconPos(int x, int y)
{
	scoreIcon->GetBlitterObject()->Set_Pos(x,y);
	scoreCryIcon->GetBlitterObject()->Set_Pos(x,y);

}


BOB * Player::GetTheCollisionBob()
{
	RECT collisionBox = this->GetCollisionBox();

	theCollisionBOB_->x = collisionBox.left;
	theCollisionBOB_->y = collisionBox.top;
	theCollisionBOB_->width = collisionBox.right - collisionBox.left + 1;
	theCollisionBOB_->height = collisionBox.bottom - collisionBox.top + 1;

	return theCollisionBOB_;

}



Player::~Player()
{

}


