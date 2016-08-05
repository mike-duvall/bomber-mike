#include "Bomb.h"


#include "../main/Globals.h"

#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"
#include "../gameobjects//ExplosionPart.h"
#include "../sound/MSound.h"
#include "../universe/Point.h"


BlitterObject * Bomb::theArchetypeBlitterObject_ = 0;

Bomb::Bomb(int x, int y, Player * aPlayer)
{

	if(theArchetypeBlitterObject_ == 0)
	{

		SetupArchetype();
	}

	theBlitterObject_ = theArchetypeBlitterObject_->Clone();
	theBlitterObject_->Set_Pos(x,y);
	hasPlayerLeft_ = false;
	myPlayer_ = aPlayer;
 	coundownTimer_ = 140;

	


}


#define NUM_FRAMES_PER_ANIMATION 4



void Bomb::SetupArchetype()
{
	int blockWidth = 32;
	int blockHeight = 32;


 	theArchetypeBlitterObject_ = new BlitterObject(0,0,blockWidth,blockHeight,32,
 		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);





	int animations[] = { 0,1,0,2 };
	string filename = "../bitmaps/Bomb.bmp";

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename.c_str(), 0, 0 );

	theArchetypeBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theArchetypeBlitterObject_->Load_Frame(dds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	theArchetypeBlitterObject_->Load_Frame(dds,2,2,0,BITMAP_EXTRACT_MODE_CELL);  

	Unload_Bitmap_File(&bitmap8bit);

	theArchetypeBlitterObject_->Load_Animation(0,4,animations);



	theArchetypeBlitterObject_->Set_Animation( 0);
	theArchetypeBlitterObject_->Set_Anim_Speed(8);
	theArchetypeBlitterObject_->Set_Vel(0,0);

}




Bomb::~Bomb()
{
	
}


bool Bomb::IsPlayerMovingOverAfterDropping(Player * aPlayer)
{
	if( (this->myPlayer_ == aPlayer) &&
		!this->hasPlayerLeft_
	  )
	{
		return TRUE;

	}
	else
	{

		return FALSE;
	}
}



void Bomb::AddFlames(int explosionSize, int xModifier, int yModifier, int type)
{
	int x = this->GetBlitterObject()->GetX();
	int y = this->GetBlitterObject()->GetY();


	int numPlacedExplosions = 0;

	bool done = false;


	int proposedX = x + xModifier;
	int proposedY = y + yModifier;


	while(!done)
	{
		Block * foundBlock = Universe::GetBlockAtPoint(proposedX + 1, proposedY + 1);
		IndestructableBlock * foundIndestructableBlock = dynamic_cast<IndestructableBlock *> (foundBlock);
		if(!foundIndestructableBlock)
		{

			// If we found a block and it wasn't an IndestructibleBlock,
			// it was a Destructible block
			// so remove it
			if(foundBlock)
			{
				Universe::RemoveBlock(foundBlock);
				delete foundBlock;
				done = true;
			}
			else
			{
				// otherwise, nothing was there so place an explosion
				Universe::GetExplosionParts().push_back(new ExplosionPart(proposedX,proposedY, type, this->GetPlayer() ));
				numPlacedExplosions++;

			}
		}

		if(
			(numPlacedExplosions == explosionSize) ||
			foundBlock
		  )
		{
			done = true;
		}

		proposedX += xModifier;
		proposedY += yModifier;

	}

}


void Bomb::AddFlamePredictedPoints(int explosionSize, int xModifier, int yModifier, POINT_VECTOR & pointVector)
{
	int x = this->GetBlitterObject()->GetX();
	int y = this->GetBlitterObject()->GetY();


	int numPlacedExplosions = 0;

	bool done = false;


	int proposedX = x + xModifier;
	int proposedY = y + yModifier;


	while(!done)
	{
// 		Block * foundBlock = Universe::GetBlockAtPoint(proposedX + 1, proposedY + 1);
		Block * foundBlock = Universe::GetBlockAtPoint(proposedX, proposedY);
		if(!foundBlock)
		{

			Point newPoint(proposedX, proposedY);
			pointVector.push_back(newPoint);
			numPlacedExplosions++;
		}

		if(
			(numPlacedExplosions == explosionSize) ||
			foundBlock
			)
		{
			done = true;
		}

		proposedX += xModifier;
		proposedY += yModifier;

	}

}






POINT_VECTOR Bomb::GetPredictedFlameLocations()
{
	POINT_VECTOR pointVector;

	int x = this->GetBlitterObject()->GetX();
	int y = this->GetBlitterObject()->GetY();

	int explosionSize = this->myPlayer_->GetExplosionSize();


// 	AddFlamePredictedPoints(explosionSize, 32,0, pointVector);

// 	// to right
// 	AddFlamePredictedPoints(explosionSize, 32, 0);
// 
// 	// to left
// 	AddFlamePredictedPoints(explosionSize, -32, 0);

	// below
	AddFlamePredictedPoints(explosionSize, 0, 32,pointVector);

// 	// above
// 	AddFlamePredictedPoints(explosionSize, 0, -32 );



	return pointVector;

}



void Bomb::AddExplosionParts()
{
	int x = this->GetBlitterObject()->GetX();
	int y = this->GetBlitterObject()->GetY();

	int explosionSize = this->myPlayer_->GetExplosionSize();

	Universe::GetExplosionParts().push_back(new ExplosionPart(x,y, EXPLOSION_PART_CENTER, this->GetPlayer() ));
	// to right
	AddFlames(explosionSize, 32, 0,EXPLOSION_PART_RIGHT_LEFT_SIDE);

	// to left
	AddFlames(explosionSize, -32, 0,EXPLOSION_PART_RIGHT_LEFT_SIDE);

	// below
	AddFlames(explosionSize, 0, 32, EXPLOSION_PART_TOP_BOTTOM_SIDE );

	// above
	AddFlames(explosionSize, 0, -32, EXPLOSION_PART_TOP_BOTTOM_SIDE );

}


bool Bomb::Update()
{

	bool removeThisBomb = false;
	coundownTimer_--;
	bool hitByExplosion = ExplosionPart::IsGameObjectInAnyExplosionPart(this);

	if(
		(coundownTimer_ <= 0) ||
		hitByExplosion
		)
	{

		removeThisBomb = true;
		Sound::PlaySound(Sound::explosion_sound);

		AddExplosionParts();
		myPlayer_->DecrementNumberOfActuallyDroppedBombs();


	}



	if(!this->hasPlayerLeft_)
	{
		BOB * playerBOB = myPlayer_->GetTheCollisionBob();
		hasPlayerLeft_ = !Collision_BOBS(playerBOB, this->GetBlitterObject()->getTheBOB());
	}


	this->GetBlitterObject()->Animate();
	return removeThisBomb;
}





bool Bomb::IsPointInBomb(int x, int y)
{
	bool isPointInBomb = FALSE;


	RECT collisionBox = GetCollisionBox();


	if(y >= collisionBox.top && y <= collisionBox.bottom && x >= collisionBox.left && x <= collisionBox.right)
	{
		isPointInBomb = TRUE;
	}

	return isPointInBomb;
}


