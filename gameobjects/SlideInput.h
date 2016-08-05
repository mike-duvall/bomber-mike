#ifndef SLIDEINPUT_H
#define SLIDEINPUT_H


#include <ddraw.h> 
#include "../t3dlib/t3dlib1.h"

class BlitterObject;
class Block;

class SlideInput
{
public:
	SlideInput(
		int aFacingDirection,
		POINT playerPosition,
		POINT leftTip,
		POINT middle,
		POINT rightTip);
);

private:

	int facingDirection;
	POINT playerPosition;
	POINT leftTip;
	POINT middle;
	POINT rightTip;




public:
};

#endif
