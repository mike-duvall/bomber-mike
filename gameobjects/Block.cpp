#include "Block.h"
//
//
//
#include "../t3dlib/t3dlib1.h"
#include "../bob/BlitterObject.h"
#include "../gameobjects/Explosion.h"
#include "../universe/Universe.h"


Block::~Block()
{
}



RECT Block::GetCollisionBox()
{
	int x = theBlitterObject_->GetX();
	int y = theBlitterObject_->GetY();
	int width = theBlitterObject_->GetWidth();
	int height= theBlitterObject_->GetHeight();

	RECT collisionBox;

	collisionBox.top = y;
	collisionBox.left = x;
	collisionBox.bottom = y + height - 1;
	collisionBox.right = x + width - 1;

	return collisionBox;
}


bool Block::IsPointInBlock(int x, int y)
{
	bool isPointInBlock = FALSE;


	RECT collisionBox = GetCollisionBox();


	if(y >= collisionBox.top && y <= collisionBox.bottom && x >= collisionBox.left && x <= collisionBox.right)
	{
		isPointInBlock = TRUE;
	}

	return isPointInBlock;
}


int Block::GetCollisionBoxMiddleX()
{
	int blockX = this->GetCollisionBox().left;

	int blockWidth = this->GetBlitterObject()->GetWidth();

	int blockMidPoint = blockX + blockWidth / 2;

	return blockMidPoint;
}

int Block::GetCollisionBoxMiddleY()
{
	int blockY = this->GetCollisionBox().top;

	int blockHeight = this->GetBlitterObject()->GetHeight();

	int blockMidPoint = blockY + blockHeight / 2;

	return blockMidPoint;
}


bool Block::Update()
{
	return false;

}

