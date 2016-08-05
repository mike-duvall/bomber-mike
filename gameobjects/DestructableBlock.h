#ifndef DESTRUCTABLE_BLOCK_H
#define DESTRUCTABLE_BLOCK_H


class BlitterObject;


#include <vector>
#include "Block.h"

using namespace std;


class DestructableBlock;


class DestructableBlock : public Block
{
public:
	DestructableBlock(int x, int y);
	virtual ~DestructableBlock();

	bool Update();



private:

	static BlitterObject * theArchetypeBlitterObject_;


public:
};

#endif
