#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H


class BlitterObject;

#include <ddraw.h> 
#include <vector>
#include "GameObject.h"

using namespace std;

class SimpleGameObject;

typedef vector<SimpleGameObject *> SIMPLE_GAME_OBJECT_VECTOR;
typedef vector<SIMPLE_GAME_OBJECT_VECTOR *> SIMPLE_GAME_OBJECT_VECTOR_VECTOR;

class SimpleGameObject : public GameObject
{
public:
	
	SimpleGameObject(int x, int y, int blockWidth, int blockHeight, const string & shortFilename,DWORD colorKey = 0);
	virtual ~SimpleGameObject();


private:


};

#endif
