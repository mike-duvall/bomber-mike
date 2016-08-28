#include "GameObject.h"



#include "../bob/BlitterObject.h"


void GameObject::Draw(LPDIRECTDRAWSURFACE7 dest)
{
	this->GetBlitterObject()->Draw(dest);
}



GameObject::~GameObject()
{
	delete theBlitterObject_;
}


BOB * GameObject::GetTheBob()
{
	return theBlitterObject_->getTheBOB();
}

