#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class Powerup;
class Player;


typedef vector<Powerup *> POWERUP_VECTOR;

class Powerup : public GameObject
{
public:
	Powerup(int x, int y ) {};
	virtual ~Powerup() {};


};

#endif
