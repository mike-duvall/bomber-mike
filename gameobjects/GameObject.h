#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "../t3dlib/t3dlib1.h"
#include <ddraw.h> 

class BlitterObject;



class GameObject
{
public:


	virtual RECT GetCollisionBox();
	void DrawCollisionBox(LPDIRECTDRAWSURFACE7 dest);
	void Draw(LPDIRECTDRAWSURFACE7 dest);
	BlitterObject * GetBlitterObject() { return theBlitterObject_; }
	BOB * GetTheBob();
	virtual BOB * GetTheCollisionBob();

	virtual ~GameObject();





protected:

	BlitterObject * theBlitterObject_;



public:
};

#endif
