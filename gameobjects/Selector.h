#ifndef SELECTOR_H
#define SELECTOR_H

#include "GameObject.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class Bomb;
class Player;

typedef vector<Bomb *> BOMB_VECTOR;

class Selector : public GameObject
{
public:
	Selector();
	virtual ~Selector();

	bool Update();


private:



};

#endif
