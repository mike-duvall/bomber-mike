#ifndef BOMBPOWERUP_H
#define BOMBPOWERUP_H

#include "PowerUp.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class BombPowerup;
class Player;


//typedef vector<BombPowerup *> BOMB_POWERUP_VECTOR;

class BombPowerup : public Powerup
{
public:
	BombPowerup(int x, int y );
	virtual ~BombPowerup() {};

	virtual void Activate(Player * aPlayer);


private:


	static BlitterObject * theArchetypeBlitterObject_;
	void SetupArchetype();


};

#endif
