#include "Explosion.h"



#include "../t3dlib/t3dlib1.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"
#include "../gameobjects/ExplosionPart.h"

// Explosion::Explosion(int x, int y)
// {
// 	coundownTimer_ = 70;
// 
// 
// 
// 	theCenterExplosionPart_ = new ExplosionPart(x,y,  0);
// 	theRightExplosionPart_  = new ExplosionPart(x + 32,y,  1);
// 
// 	theBottomExplosionPart_ = new ExplosionPart(x,y +32,  2);
// 	theLeftExplosionPart_ = new ExplosionPart(x - 32,y,  1);
// 	theTopExplosionPart_ = new ExplosionPart(x,y - 32,  2);
// 
// 
// 
// 
// }


Explosion::~Explosion()
{
	delete theCenterExplosionPart_;
	delete theRightExplosionPart_;
	delete theBottomExplosionPart_;
	delete theLeftExplosionPart_;
	delete theTopExplosionPart_;
}


void Explosion::Draw(LPDIRECTDRAWSURFACE7 lpddsback)
{

	theCenterExplosionPart_->Draw(lpddsback);
	theRightExplosionPart_->Draw(lpddsback);
	theBottomExplosionPart_->Draw(lpddsback);
	theLeftExplosionPart_->Draw(lpddsback);
	theTopExplosionPart_->Draw(lpddsback);

}



bool Explosion::Update()
{

	bool removeThisExplosion = false;
	coundownTimer_--;
	if(coundownTimer_ <=0)
	{
		removeThisExplosion = true;
	}
	theCenterExplosionPart_->GetBlitterObject()->Animate();
	theRightExplosionPart_->GetBlitterObject()->Animate();
	theBottomExplosionPart_->GetBlitterObject()->Animate();
	theLeftExplosionPart_->GetBlitterObject()->Animate();
	theTopExplosionPart_->GetBlitterObject()->Animate();

	return removeThisExplosion;
}
