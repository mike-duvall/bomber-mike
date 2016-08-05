#ifndef BLOCK_H
#define BLOCK_H


#include "GameObject.h"

class BlitterObject;

#include <ddraw.h> 
#include <vector>

using namespace std;


class Block;

typedef vector<Block *> BLOCK_VECTOR;

class Block  : public GameObject
{
public:
	virtual ~Block();

	virtual bool Update();
	RECT GetCollisionBox();
	int GetCollisionBoxMiddleX();
	int GetCollisionBoxMiddleY();
	bool IsPointInBlock(int x, int y);


//	BlitterObject * GetBlitterObject() { return theBlitterObject_; }

protected:
//	BlitterObject * theBlitterObject_;


public:
};

#endif
