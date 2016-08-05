#include "GameObject.h"



#include "../bob/BlitterObject.h"



void GameObject::Draw(LPDIRECTDRAWSURFACE7 dest)
{
	this->GetBlitterObject()->Draw(dest);
}

RECT GameObject::GetCollisionBox()
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


GameObject::~GameObject()
{
	delete theBlitterObject_;
}


BOB * GameObject::GetTheBob()
{
	return theBlitterObject_->getTheBOB();
}

BOB * GameObject::GetTheCollisionBob()
{
	return this->GetTheBob();
}


void GameObject::DrawCollisionBox(LPDIRECTDRAWSURFACE7 dest)
{


	int pitch;
	UCHAR * surface;
	surface = DDraw_Lock_Surface(dest, &pitch);

	int color = 211; // yellow

	RECT boundingBox = GetCollisionBox();

	// top line
	HLine(boundingBox.left, boundingBox.right, boundingBox.top, color, surface, pitch );

	// bottom line
	HLine(boundingBox.left, boundingBox.right, boundingBox.bottom, color, surface, pitch );

	// right line
	VLine(boundingBox.top, boundingBox.bottom, boundingBox.right, color, surface, pitch);

	// left line
	VLine(boundingBox.top, boundingBox.bottom, boundingBox.left, color, surface, pitch);

	DDraw_Unlock_Surface(dest);

}
