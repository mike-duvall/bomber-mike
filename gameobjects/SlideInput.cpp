#include "Player.h"




#include "../t3dlib/t3dlib1.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"
#include "../gameobjects/Block.h"

#include "ControlEvent.h"


#define EAST         0
#define NEAST        1  
#define NORTH        2
#define NWEST        3
#define WEST         4
#define SWEST        5
#define SOUTH        6
#define SEAST        7


#include "Block.h"


bool Player::CheckForBlockCollision2(Block * aBlock, int dx, int dy)
{
	bool fIsCollision = false;

	int x = theBlitterObject_->GetX();
	int y = theBlitterObject_->GetY();
	int width = theBlitterObject_->GetWidth();
	int height= theBlitterObject_->GetHeight();

	boxTopLeftX = x + 6;
	boxTopLeftY = y + 12;
	boxBottomRightX = x  + 6 + 32 - 1;
	boxBottomRightY = y +  12 + 32 - 1;


	boxTopLeftX += dx;
	boxTopLeftY += dy;
	boxBottomRightX += dx;
	boxBottomRightY += dy;



	if(boxBottomRightY <= aBlock->GetBlitterObject()->GetY())
	{
		return fIsCollision;
	}

	if(boxTopLeftY > (aBlock->GetBlitterObject()->GetY() + aBlock->GetBlitterObject()->GetHeight() - 1))
	{
		return fIsCollision;
	}

	if(boxTopLeftX > aBlock->GetBlitterObject()->GetX() + aBlock->GetBlitterObject()->GetWidth() - 1 )
	{
		return fIsCollision;
	}


	if(boxBottomRightX >= aBlock->GetBlitterObject()->GetX())
	{
		return true;
	}

	return false;

}



bool Player::IsBlockImmediatelyBelow(Block * aBlock)
{
	bool fIsBlockBelow = FALSE;
	fIsBlockBelow = CheckForBlockCollision2(aBlock, 0, moveIncrementAmount);
	return fIsBlockBelow;
}


bool Player::IsBlockImmediatelyToTheRight(Block * aBlock)
{
	bool fIsBlockBelow = FALSE;
	fIsBlockBelow = CheckForBlockCollision2(aBlock, moveIncrementAmount, 0);
	return fIsBlockBelow;
}




Block *  Player::GetBlockImmediatelyBelow()
{
	

	BLOCK_VECTOR::iterator theBlockIterator;

	for(	theBlockIterator = Universe::GetBlocks().begin();
		theBlockIterator != Universe::GetBlocks().end();
		theBlockIterator++
		)
	{
		Block * nextBlock = *theBlockIterator;
		if(IsBlockImmediatelyBelow(nextBlock))
		{
			return nextBlock;
		}

	
	}

	return 0;

}


Block *  Player::GetBlockImmediatelyToTheRight()
{


	BLOCK_VECTOR::iterator theBlockIterator;

	for(	theBlockIterator = Universe::GetBlocks().begin();
		theBlockIterator != Universe::GetBlocks().end();
		theBlockIterator++
		)
	{
		Block * nextBlock = *theBlockIterator;
		if(IsBlockImmediatelyToTheRight(nextBlock))
		{
			return nextBlock;
		}


	}

	return 0;

}







//Block * Player::GetBlockToLeftOfBlock(Block * aBlock)
//{
//	BLOCK_VECTOR::iterator theBlockIterator;
//
//	for(	theBlockIterator = Universe::GetBlocks().begin();
//		theBlockIterator != Universe::GetBlocks().end();
//		theBlockIterator++
//		)
//	{
//		Block * nextBlock = *theBlockIterator;
//		if(IsBlockImmediatelyBelow(nextBlock))
//		{
//			return nextBlock;
//		}
//
//
//	}
//
//	return 0;
//
//
//
//}




// bool Player::IsPlayerOnLeftSideOfBlock(Block * aBlock)
// {
// 
// 	bool isOnLeft = false;
// 	int myCollisionBoxLeftX = this->GetCollisionBox().left;
// 	int myCollisionBoxRightX = this->GetCollisionBox().right;
// 	int myCollisionBoxWidth = myCollisionBoxRightX - myCollisionBoxLeftX;
// 	int myCollisionBoxHalfWidth = myCollisionBoxWidth / 2;
// 
// 	int myCollisionBoxCenterX = myCollisionBoxLeftX + myCollisionBoxHalfWidth;
// 
// 	int blockX = aBlock->GetBlitterObject()->GetX();
// 	int blockWidth = aBlock->GetBlitterObject()->GetWidth();
// 
// 	int halfWidth = int(blockWidth / 2.0);
// 	int blockMidPoint = halfWidth + blockX;
// 
// 	if(myCollisionBoxCenterX <= blockMidPoint)
// 	{
// 		isOnLeft = true;
// 	}
// 
// 	return isOnLeft;
// 
// }



bool Player::IsPlayerInLeftMiddleOfBlock(Block * aBlock)
{
	bool isInMiddleLeft = false;

	int myCollisionBoxCenterX = GetCollisionBoxCenterX();

//	int blockX = aBlock->GetBlitterObject()->GetX();

	int leftTip = aBlock->GetLeftTip();


	int blockMidPoint = aBlock->GetCollisionBoxMiddleX();

	if(  (myCollisionBoxCenterX < blockMidPoint) &&
		 (myCollisionBoxCenterX > leftTip)
		
	  )
	{
		isInMiddleLeft = true;
	}

	return isInMiddleLeft;
}


bool Player::IsPlayerInUpperMiddleOfBlock(Block * aBlock)
{
	bool isInUpperMiddle = false;

	int myCollisionBoxCenterY = GetCollisionBoxCenterY();

//	int blockY = aBlock->GetBlitterObject()->GetY();

	int upperTip = aBlock->GetUpperTip();


	int blockMidPoint = aBlock->GetCollisionBoxMiddleY();

	if(  (myCollisionBoxCenterY < blockMidPoint) &&
		(myCollisionBoxCenterY > upperTip)

		)
	{
		isInUpperMiddle = true;
	}

	return isInUpperMiddle;
}







bool Player::IsPlayerInRightMiddleOfBlock(Block * aBlock)
{
	bool isInMiddleRight = false;

	int myCollisionBoxCenterX = GetCollisionBoxCenterX();

	int blockX = aBlock->GetBlitterObject()->GetX();

	int rightTip = aBlock->GetRightTip();


	int blockMidPoint = aBlock->GetCollisionBoxMiddleX();

	if(  (myCollisionBoxCenterX > blockMidPoint) &&
		(myCollisionBoxCenterX < rightTip)

		)
	{
		isInMiddleRight = true;
	}

	return isInMiddleRight;
}


bool Player::IsPlayerInLowerMiddleOfBlock(Block * aBlock)
{
	bool isInLowerMiddle = false;

	int myCollisionBoxCenterY = GetCollisionBoxCenterY();

	int lowerTip = aBlock->GetLowerTip();

	int blockMidPoint = aBlock->GetCollisionBoxMiddleY();

	if(  (myCollisionBoxCenterY > blockMidPoint) &&
		(myCollisionBoxCenterY < lowerTip)

		)
	{
		isInLowerMiddle = true;
	}

	return isInLowerMiddle;
}








int Player::GetCollisionBoxCenterX()
{
	int myCollisionBoxLeftX = this->GetCollisionBox().left;
	int myCollisionBoxRightX = this->GetCollisionBox().right;
	int myCollisionBoxWidth = myCollisionBoxRightX - myCollisionBoxLeftX;
	int myCollisionBoxHalfWidth = myCollisionBoxWidth / 2;
	int myCollisionBoxCenterX = myCollisionBoxLeftX + myCollisionBoxHalfWidth;

	return myCollisionBoxCenterX;

}

int Player::GetCollisionBoxCenterY()
{
	int myCollisionBoxUpperY = this->GetCollisionBox().top;
	int myCollisionBoxLowerY = this->GetCollisionBox().bottom;
	int myCollisionBoxWidth = myCollisionBoxLowerY - myCollisionBoxUpperY;
	int myCollisionBoxHalfWidth = myCollisionBoxWidth / 2;
	int myCollisionBoxCenterY = myCollisionBoxUpperY + myCollisionBoxHalfWidth;

	return myCollisionBoxCenterY;
}





bool Player::IsPlayerInLeftTip(Block * aBlock)
{
	bool isInLeftTip = false;

	int myCollisionBoxCenterX = GetCollisionBoxCenterX();

	int blockX = aBlock->GetBlitterObject()->GetX();

    int leftTip = aBlock->GetLeftTip();

    if( myCollisionBoxCenterX <= leftTip)
	{
      isInLeftTip = true;
	}

	return isInLeftTip;
	
}


bool Player::IsPlayerInUpperTip(Block * aBlock)
{
	bool isInUpperTip = false;

	int myCollisionBoxCenterY = GetCollisionBoxCenterY();


	int blockY = aBlock->GetBlitterObject()->GetY();

	int upperTip = aBlock->GetUpperTip();

	if( myCollisionBoxCenterY <= upperTip)
	{
		isInUpperTip = true;
	}

	return isInUpperTip;

}






bool Player::IsPlayerInRightTip(Block * aBlock)
{
	bool isInRightTip = false;

	int myCollisionBoxCenterX = GetCollisionBoxCenterX();

	int blockX = aBlock->GetBlitterObject()->GetX();

	int leftTip = aBlock->GetRightTip();

	if( myCollisionBoxCenterX >= leftTip)
	{
		isInRightTip = true;
	}

	return isInRightTip;
}



bool Player::IsPlayerInLowerTip(Block * aBlock)
{
	bool isInLowerTip = false;

	int myCollisionBoxCenterY = GetCollisionBoxCenterY();

	int lowerTip = aBlock->GetLowerTip();

	if( myCollisionBoxCenterY >= lowerTip )
	{
		isInLowerTip = true;
	}

	return isInLowerTip;
}







void Player::HandleMoveDownInLeftTip()
{

	if(  (this->GetBlitterObject()->Get_Current_Animation() == WEST)  ||
		(this->GetBlitterObject()->Get_Current_Animation() == SOUTH) 
		)
	{
		// Slide down and left
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
		this->GetBlitterObject()->IncrementX(-moveIncrementAmount);

	}

}

 
void Player::HandleMoveRightInUpperTip()
{

	if(  (this->GetBlitterObject()->Get_Current_Animation() == NORTH)  ||
		(this->GetBlitterObject()->Get_Current_Animation() == EAST) 
		)
	{
		// Slide down and left
		this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);

	}

}






void Player::HandleMoveDownInRightTip()
{
	if(  (this->GetBlitterObject()->Get_Current_Animation() == EAST)  ||
		(this->GetBlitterObject()->Get_Current_Animation() == SOUTH) 
		)
	{
		// Slide down and left
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	}
}


void Player::HandleMoveRightInLowerTip()
{
	if(  (this->GetBlitterObject()->Get_Current_Animation() == SOUTH)  ||
		(this->GetBlitterObject()->Get_Current_Animation() == EAST) 
		)
	{
		// Slide down and left
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	}
}








void Player::HandleMoveDownInLeftMiddle()
{
	int currentAnimation = this->GetBlitterObject()->Get_Current_Animation(); 
	if(  ( currentAnimation == WEST)  ||
		 ( currentAnimation == SOUTH) 
		)
	{
		this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
		if (currentAnimation != WEST)
		{
			this->GetBlitterObject()->Set_Animation(WEST);
		}
	}

	else if ( currentAnimation == EAST)
	{
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	}

} 


void Player::HandleMoveRightInUpperMiddle()
{
	int currentAnimation = this->GetBlitterObject()->Get_Current_Animation(); 
	if(  ( currentAnimation == NORTH)  ||
		( currentAnimation == EAST) 
		)
	{
		this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
		if (currentAnimation != NORTH)
		{
			this->GetBlitterObject()->Set_Animation(NORTH);
		}
	}

	else if ( currentAnimation == SOUTH)
	{
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	}

} 





void Player::HandleMoveDownInRightMiddle()
{
	int currentAnimation = this->GetBlitterObject()->Get_Current_Animation(); 
	if(  (currentAnimation == EAST)  ||
		(currentAnimation == SOUTH) 
		)
	{
		this->GetBlitterObject()->IncrementX(moveIncrementAmount);
		if (currentAnimation != EAST)
			this->GetBlitterObject()->Set_Animation(EAST);
	}
	else if ( currentAnimation == WEST)
	{
		this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	}
}


void Player::HandleMoveRightInLowerMiddle()
{
	int currentAnimation = this->GetBlitterObject()->Get_Current_Animation(); 
	if(  (currentAnimation == NORTH)  ||
		(currentAnimation == EAST) 
		)
	{
		this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
		if (currentAnimation != NORTH)
			this->GetBlitterObject()->Set_Animation(NORTH);
	}
	else if ( currentAnimation == SOUTH)
	{
		this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	}
}









void Player::HandleMoveDownWithBlockBelow(Block * aBlock)
{

	if( IsPlayerInLeftTip(aBlock))
	{
		HandleMoveDownInLeftTip();
	}
	
	else if( IsPlayerInLeftMiddleOfBlock(aBlock) )
	{
		HandleMoveDownInLeftMiddle();
	}
	else if( IsPlayerInRightTip(aBlock))
	{
		HandleMoveDownInRightTip();	
	}
	else if( IsPlayerInRightMiddleOfBlock(aBlock) )
	{
		HandleMoveDownInRightMiddle();
	}

}
 

void Player::HandleMoveRightWithBlockToTheRight(Block * aBlock)
{

	// block center
	int blockCenterX = aBlock->GetCollisionBoxMiddleX();
	int blockCenterY = aBlock->GetCollisionBoxMiddleY();

	// upper tip (translates to right tip)
	int upperTipX = aBlock->GetBlitterObject()->GetX();
	int upperTipY = aBlock->GetUpperTip();

	// middle of left edge (translates to middle of top edge)
	int middleLeftEdgeX = aBlock->GetBlitterObject()->GetX();;
	int middleLeftEdgeY = aBlock->GetCollisionBoxMiddleY();

	// lower tip (translates to left tip)
	int lowerTipX = aBlock->GetBlitterObject()->GetX();
	int lowerTipY = aBlock->GetLowerTip();

	// Player center right edge (translates to player center bottom edge)
	int playerCenterRightEdgeX = this->GetCollisionBox().right;
	int playerCenterRightEdgeY = GetCollisionBoxCenterY();



	slidePolygon.state = 1;
	slidePolygon.num_verts = 5;
	slidePolygon.x0 = blockCenterX;
	slidePolygon.y0 = blockCenterY;
	slidePolygon.xv = 0;
	slidePolygon.yv = 0;
	slidePolygon.color = 255;
	slidePolygon.vlist = new VERTEX2DF[slidePolygon.num_verts];

	VERTEX2DF center;
	VERTEX2DF lowerTip;
	VERTEX2DF midleLeftEdge;
	VERTEX2DF upperTip;
	VERTEX2DF playerCenterRightEdge;


	center.x = 0;
	center.y = 0;

	lowerTip.x = float(lowerTipX - blockCenterX);
	lowerTip.y = float(lowerTipY - blockCenterY);

	midleLeftEdge.x = float(middleLeftEdgeX - blockCenterX);
	midleLeftEdge.y = 0;

	upperTip.x = float(upperTipX - blockCenterX);
	upperTip.y = float(upperTipY - blockCenterY);

	playerCenterRightEdge.x = float(playerCenterRightEdgeX - blockCenterX);
	playerCenterRightEdge.y = float(playerCenterRightEdgeY - blockCenterY);
 
	slidePolygon.vlist[0] = center;
	slidePolygon.vlist[1] = lowerTip;
	slidePolygon.vlist[2] = midleLeftEdge;
	slidePolygon.vlist[3] = playerCenterRightEdge;
	slidePolygon.vlist[4] = upperTip;

//	Rotate_Polygon2D( &slidePolygon,90 );

	isPolygonActive = true;



	if( IsPlayerInUpperTip(aBlock))
	{
      HandleMoveRightInUpperTip();
	}
	else if( IsPlayerInUpperMiddleOfBlock(aBlock) )
	{
		HandleMoveRightInUpperMiddle();
	}
	else if( IsPlayerInLowerTip(aBlock))
	{
		HandleMoveRightInLowerTip();	
	}
	else if( IsPlayerInLowerMiddleOfBlock(aBlock) )
	{
		HandleMoveRightInLowerMiddle();
	}


/*****************************************************/
/*****************************************************/
/*****************************************************/
/*****************************************************/


// 	if( IsPlayerInLeftTip(aBlock))
// 	{
// 		HandleMoveDownInLeftTip();
// 	}
// 
// 	else if( IsPlayerInLeftMiddleOfBlock(aBlock) )
// 	{
// 		HandleMoveDownInLeftMiddle();
// 	}
// 	else if( IsPlayerInRightTip(aBlock))
// 	{
// 		HandleMoveDownInRightTip();	
// 	}
// 	else if( IsPlayerInRightMiddleOfBlock(aBlock) )
// 	{
// 		HandleMoveDownInRightMiddle();
// 	}

}






void Player::HandleMoveDownWithNoBlockBelow()
{
	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
		this->GetBlitterObject()->Set_Animation(SOUTH);
	this->GetBlitterObject()->Animate();
}

void Player::HandleMoveRightWithNoBlockToTheRight()
{
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != EAST)
		this->GetBlitterObject()->Set_Animation(EAST);
	this->GetBlitterObject()->Animate();
}



void Player::HandleMoveDown()
{
	Block * blockBelow = GetBlockImmediatelyBelow();

	if(!blockBelow)
	{
	  HandleMoveDownWithNoBlockBelow();
	}
	else
	{
	  HandleMoveDownWithBlockBelow(blockBelow);
	}

}


void Player::HandleMoveRight()
{
	Block * blockToTheRight = GetBlockImmediatelyToTheRight();

	if( !blockToTheRight )
	{
	  HandleMoveRightWithNoBlockToTheRight();

	}
	else
	{
	  HandleMoveRightWithBlockToTheRight(blockToTheRight);
	}

}


void Player::HandleMoveLeft()
{
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);

	if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
	{
		this->GetBlitterObject()->Set_Animation(WEST);
	}
	this->GetBlitterObject()->Animate();

}


void Player::HandleMoveUp()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);

	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
	{
		this->GetBlitterObject()->Set_Animation(NORTH);
	}
	this->GetBlitterObject()->Animate();

}




void Player::Update(int controlEvent)
{
	switch(controlEvent)
	{
	case CONTROL_EVENT_MOVE_SOUTH:
		HandleMoveDown();
		break;
	case CONTROL_EVENT_MOVE_EAST:
		HandleMoveRight();
		break;
	case CONTROL_EVENT_MOVE_WEST:
		HandleMoveLeft();
		break;

	case CONTROL_EVENT_MOVE_NORTH:
		HandleMoveUp();
		break;


	}
}


//void Player::Update(int controlEvent)
//{
//	int dx = 0;
//	int dy = 0;
//	int player_moving = 0;
//	if (controlEvent == CONTROL_EVENT_MOVE_EAST )
//	{
//		this->GetBlitterObject()->IncrementX(2);
//		dx=2; dy=0;
//		player_moving = 1;
//		// check animation needs to change
//		if (this->GetBlitterObject()->Get_Current_Animation() != EAST)
//				this->GetBlitterObject()->Set_Animation(EAST);
//	} 
//	else
//	if (controlEvent == CONTROL_EVENT_MOVE_WEST )
//	{
//		this->GetBlitterObject()->IncrementX(-2);
//		dx=-2; dy=0; 
//		player_moving = 1;
//
//		if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
//			this->GetBlitterObject()->Set_Animation(WEST);
//
//	} // end if
//	else
//	if (controlEvent == CONTROL_EVENT_MOVE_NORTH)
//	{
//		this->GetBlitterObject()->IncrementY(-2);
//		dx=0; dy=-2;
//		player_moving = 1;
//
//		// check animation needs to change
//		if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
//			this->GetBlitterObject()->Set_Animation(NORTH);
//	}
//	else
//	if (controlEvent == CONTROL_EVENT_MOVE_SOUTH)
//	{
//		this->GetBlitterObject()->IncrementY(2);
//		dx=0; dy=+2;
//		player_moving = 1;
//	
//		// check animation needs to change
//		if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
//			this->GetBlitterObject()->Set_Animation(SOUTH);
//	}
//	else
//	if ( (controlEvent == CONTROL_EVENT_DROP_BOMB) && (bombDropCoundownTimer <= 0))
//	{
//		int x = this->GetBlitterObject()->GetX();
//		int y = this->GetBlitterObject()->GetY();
//
//		Universe::GetBombs().push_back(new Bomb( x + 6, y + 12 ));
//		bombDropCoundownTimer = 10;
//	}
//
//	bombDropCoundownTimer--;
//
//
//	// only animate if player is moving
//	if (player_moving)
//	{
//		this->GetBlitterObject()->Animate();
//
//		// check if skelaton is off screen
//		if (this->GetBlitterObject()->GetX() < 0 || this->GetBlitterObject()->GetX() > (screen_width - this->GetBlitterObject()->GetWidth()))
//			this->GetBlitterObject()->IncrementX(-dx);
//
//
//		if (this->GetBlitterObject()->GetY() < 0 || this->GetBlitterObject()->GetY() > (screen_height - this->GetBlitterObject()->GetHeight()))
//			this->GetBlitterObject()->IncrementY(-dy);
//
//	} 
//
//
//
//	BLOCK_VECTOR::iterator theBlockIterator;
//
//	for(	theBlockIterator = Universe::GetBlocks().begin();
//		theBlockIterator != Universe::GetBlocks().end();
//		theBlockIterator++
//		)
//	{
//		Block * nextBlock = *theBlockIterator;
//		CheckForBlockCollision( nextBlock,dx,dy);
//	}
//
//
//
//}


RECT Player::GetCollisionBox()
{
	int playerX = theBlitterObject_->GetX();
	int playerY = theBlitterObject_->GetY();
	int playerWidth = theBlitterObject_->GetWidth();
	int playerHeight= theBlitterObject_->GetHeight();

	boxTopLeftX = playerX + 6;
	boxTopLeftY = playerY + 12;
	boxBottomRightX = playerX  + 6 + 32 - 1;
	boxBottomRightY = playerY +  12 + 32 - 1;

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

	int drawBoundingBox = 1;

	if(drawBoundingBox)
	{
		int pitch;
		UCHAR * surface;
		surface = DDraw_Lock_Surface(dest, &pitch);

		int color = 211; // yellow

		RECT boundingBox = GetCollisionBox();
 
		// top line
		HLine(boundingBox.left, boundingBox.right, boundingBox.top, color, surface, pitch );

		// bottom line
//		HLine(boundingBox.left, boundingBox.right, boundingBox.bottom, color, surface, pitch );

		// center dot on bottom line
		int centerX = GetCollisionBoxCenterX();
		Draw_Pixel(centerX, boundingBox.bottom,255,
			surface, pitch );


		

		// right line
//		VLine(boundingBox.top, boundingBox.bottom, boundingBox.right, color, surface, pitch);
		int centerY = GetCollisionBoxCenterY();
		Draw_Pixel(boundingBox.right, centerY,255,
			surface, pitch );


 
		// left line
		VLine(boundingBox.top, boundingBox.bottom, boundingBox.left, color, surface, pitch);




		if(isPolygonActive)
		{
			Draw_Polygon2D(&slidePolygon,surface,pitch  );
		}




		DDraw_Unlock_Surface(dest);
	}
}

Player::Player(int x, int y)
{

	isPolygonActive = false; 

	moveIncrementAmount = 2;
	int playerWidth = 44;
	int playerHeight = 44;

	int numFrames = 32;
	int transparentColorKey = 143;

	bombDropCoundownTimer = 0;

	// create skeleton bob
	theBlitterObject_ = new BlitterObject(x,y,playerWidth,playerHeight,numFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_SYSTEMMEMORY, transparentColorKey);


	// animation sequences for bob
	int skelaton_anims[8][4] = { {0,1,0,2},
	{0+4,1+4,0+4,2+4},
	{0+8,1+8,0+8,2+8},
	{0+12,1+12,0+12,2+12},
	{0+16,1+16,0+16,2+16},
	{0+20,1+20,0+20,2+20},
	{0+24,1+24,0+24,2+24},
	{0+28,1+28,0+28,2+28}, };



	// load the frames in 8 directions, 4 frames each
	// each set of frames has a walk and a fire, frame sets
	// are loaded in counter clockwise order looking down
	// from a birds eys view or the x-z plane
	for (int direction = 0; direction < 8; direction++)
	{ 
		char filename[80];

		// build up file name
		sprintf(filename,"../bitmaps/SKELSP%d.BMP",direction);

		// load in new bitmap file
		Load_Bitmap_File(&bitmap8bit,filename);

		theBlitterObject_->Load_Frame(&bitmap8bit,0+direction*4,0,0,BITMAP_EXTRACT_MODE_CELL);  
		theBlitterObject_->Load_Frame(&bitmap8bit,1+direction*4,1,0,BITMAP_EXTRACT_MODE_CELL);  
		theBlitterObject_->Load_Frame(&bitmap8bit,2+direction*4,2,0,BITMAP_EXTRACT_MODE_CELL);  
		theBlitterObject_->Load_Frame(&bitmap8bit,3+direction*4,0,1,BITMAP_EXTRACT_MODE_CELL);  


		// unload the bitmap file
		Unload_Bitmap_File(&bitmap8bit);

		// set the animation sequences for skelaton

		theBlitterObject_->Load_Animation(direction,4,skelaton_anims[direction]);

	} // end for direction


	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);
//	theBlitterObject_->Set_Pos(0,128);


}


Player::~Player()
{
	delete theBlitterObject_;
}