#include "ExplosionPart.h"



#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"


BlitterObject * ExplosionPart::theArchetypeBlitterObject_[3] =  {0,0,0};

ExplosionPart::ExplosionPart(int x, int y, int aType, Player * aPlayer)
{


	myPlayer_ = aPlayer;
	if(theArchetypeBlitterObject_[aType] == 0)
	{

		type_ = aType;
		coundownTimer_ = 70;
		int blockWidth = 32;
		int blockHeight = 32;


		int transparentColorKey = RGB(0,107,0);

		theArchetypeBlitterObject_[aType] = new BlitterObject(x,y,blockWidth,blockHeight,32,
			BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);


		int block_anims[1][7] = { {0,1,2,3,2,1,0}, };


		// load the frames in 8 directions, 4 frames each
		// each set of frames has a walk and a fire, frame sets
		// are loaded in counter clockwise order looking down
		// from a birds eys view or the x-z plane
		for (int direction = 0; direction < 1; direction++)
		{ 
			char filename[80];
			// build up file name
			sprintf(filename,"../bitmaps/CenterExplosion%d.BMP",direction);

			// load in new bitmap file
//			Load_Bitmap_File(&bitmap8bit,filename);
			IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename, 0, 0 );

			theArchetypeBlitterObject_[aType]->Load_Frame(dds,0+direction*4,0,type_ ,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_[aType]->Load_Frame(dds,1+direction*4,1,type_ ,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_[aType]->Load_Frame(dds,2+direction*4,2,type_,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_[aType]->Load_Frame(dds,3+direction*4,3,type_,BITMAP_EXTRACT_MODE_CELL);  


			// unload the bitmap file
			Unload_Bitmap_File(&bitmap8bit);


			theArchetypeBlitterObject_[aType]->Load_Animation(direction,7,block_anims[direction]);

		} // end for direction


		theArchetypeBlitterObject_[aType]->Set_Animation( 0);
		theArchetypeBlitterObject_[aType]->Set_Anim_Speed(8);
		theArchetypeBlitterObject_[aType]->Set_Vel(0,0);
	}

	theBlitterObject_ = theArchetypeBlitterObject_[aType]->Clone();
	theBlitterObject_->Set_Pos(x,y);
	theBlitterObject_->Set_Animation( 0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);
	type_ = aType;
	coundownTimer_ = 30;
	


}


ExplosionPart::~ExplosionPart()
{

}


bool ExplosionPart::IsGameObjectInAnyExplosionPart(GameObject * aGameObject)
{

	EXPLOSIONPART_VECTOR::iterator theExplosionPartIterator;

	for(	theExplosionPartIterator = Universe::GetExplosionParts().begin();
		theExplosionPartIterator != Universe::GetExplosionParts().end();
		theExplosionPartIterator++
		)
	{
		ExplosionPart * nextExplosionPart = *theExplosionPartIterator;



		bool isBombInExplosion = nextExplosionPart->IsBlitterObjectInThisExplosionPart(aGameObject);

		if(isBombInExplosion)
		{
			return true;
		}

	}

	return false;


}

int Collision_BOBS_Half_Overlap(BOB_PTR bob1, BOB_PTR bob2);


bool ExplosionPart::IsBlitterObjectInThisExplosionPart(GameObject * aGameObject)
{

	BOB * gameObjectBOB = aGameObject->GetTheCollisionBob();
	BOB * myBOB = this->GetBlitterObject()->getTheBOB();
	

	int collision = Collision_BOBS_Half_Overlap(gameObjectBOB,myBOB);
	if(collision)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
//	return 	(bool) Collision_BOBS_Half_Overlap(gameObjectBOB,myBOB);


}





bool ExplosionPart::IsPointInExplosionPart(int x, int y )
{
	bool fPointIsInExplosionPart = false;

	int blockX = theBlitterObject_->GetX();
	int blockY = theBlitterObject_->GetY();

	int blockWidth = theBlitterObject_->GetWidth();
	int blockHeight = theBlitterObject_->GetHeight();

	if(  (x >= blockX)                     &&
		 (x <= (blockX + blockWidth) )     &&
		 (y >= blockY)                     &&
		 (y <= blockY + blockHeight)
		)
	{
	fPointIsInExplosionPart = true;
	}
	return fPointIsInExplosionPart;
}




bool ExplosionPart::IsPointInExplosionPartSquare(int x, int y)
{
	bool isPointInExplosionPartSquare = FALSE;


	RECT collisionBox = GetCollisionBox();


	if(y >= collisionBox.top && y <= collisionBox.bottom && x >= collisionBox.left && x <= collisionBox.right)
	{
		isPointInExplosionPartSquare = TRUE;
	}

	return isPointInExplosionPartSquare;
}



bool ExplosionPart::Update()
{

	bool removeThisExplosionPart = false;
	coundownTimer_--;
	if(coundownTimer_ <=0)
	{
		removeThisExplosionPart = true;
	}
	this->GetBlitterObject()->Animate();
	return removeThisExplosionPart;
}



bool ExplosionPart::DoesRectangleOverlap(RECT rectangle)
{

	RECT myCollisionBox = this->GetCollisionBox();
	int x1 = myCollisionBox.left;
	int y1 = myCollisionBox.bottom;
	int w1 = myCollisionBox.right - myCollisionBox.left + 1;
	int h1 = myCollisionBox.bottom - myCollisionBox.top + 1;

	int x2 = rectangle.left;
	int y2 = rectangle.bottom;
	int w2 = rectangle.right - rectangle.left + 1;
	int h2 = rectangle.bottom - rectangle.top + 1;

 


	bool collsion = Collision_Test_Mike_Fix( 
		x1,  y1, w1, h1, 
		x2,  y2, w2, h2) ;


	return collsion;

}



//void ExplosionPart::Draw(LPDIRECTDRAWSURFACE7 lpddsback)
//{

	//int x = this->GetCollisionBox().left + 5;
	//int y = this->GetCollisionBox().top + 5;
	//Block * aBlock = Universe::GetBlockAtPoint(x,y);
	//if(!aBlock)
	//{
	//	theBlitterObject_->Draw(lpddsback);

	//	int drawBoundingBox = 0;

	//	if(drawBoundingBox)
	//	{
	//		this->DrawCollisionBox(lpddsback);
	//	}
	//}


//}