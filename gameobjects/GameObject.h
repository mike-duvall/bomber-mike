#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "../t3dlib/t3dlib1.h"
#include <ddraw.h> 

class BlitterObject;



class GameObject
{
public:


	void Draw(LPDIRECTDRAWSURFACE7 dest);
	BlitterObject * GetBlitterObject() { return theBlitterObject_; }
	BOB * GetTheBob();
	virtual ~GameObject();


protected:

	BlitterObject * theBlitterObject_;



public:
};

#endif
