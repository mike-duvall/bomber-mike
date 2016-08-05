#ifndef INDESTRUCTABLE_BLOCK_H
#define INDESTRUCTABLE_BLOCK_H


class BlitterObject;

#include <ddraw.h> 
#include <vector>
#include "Block.h"

using namespace std;




class IndestructableBlock : public Block
{
public:
	IndestructableBlock(int x, int y);
	virtual ~IndestructableBlock();


private:
	static BlitterObject * theArchetypeBlitterObject_;



public:
};

#endif
