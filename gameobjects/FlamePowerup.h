#ifndef FLAMEPOWERUP_H
#define FLAMEPOWERUP_H

#include "Powerup.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class FlamePowerup;
class Player;


//typedef vector<FlamePowerup *> FLAME_POWERUP_VECTOR;

class FlamePowerup : public Powerup
{
public:
	FlamePowerup(int x, int y );
	virtual ~FlamePowerup() {};

	virtual void Activate(Player * aPlayer);



private:


	static BlitterObject * theArchetypeBlitterObject_;
	void SetupArchetype();


};

#endif
