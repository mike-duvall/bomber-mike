#ifndef EXPLOSIONPART_H
#define EXPLOSIONPART_H


#include "GameObject.h"

#include <ddraw.h> 

class BlitterObject;


#include <vector>

using namespace std;


class ExplosionPart;
class Player;

typedef vector<ExplosionPart *> EXPLOSIONPART_VECTOR;

#define EXPLOSION_PART_CENTER 0
#define EXPLOSION_PART_RIGHT_LEFT_SIDE 1
#define EXPLOSION_PART_TOP_BOTTOM_SIDE 2

class ExplosionPart : public GameObject
{
public:
	ExplosionPart(int x, int y, int type, Player * aPlayer);
	virtual ~ExplosionPart();

	bool Update();
//	void Draw(LPDIRECTDRAWSURFACE7 lpddsback);

	bool DoesRectangleOverlap(RECT rectangle);

	bool IsPointInExplosionPart(int x, int y );
	bool IsBlitterObjectInThisExplosionPart(GameObject * aGameObject);
	static bool IsGameObjectInAnyExplosionPart(GameObject * aGameObject);
	bool IsPointInExplosionPartSquare(int x, int y);
	Player * GetPlayer() { return myPlayer_;}

private:
	int coundownTimer_;
	int type_;

	static BlitterObject * theArchetypeBlitterObject_[3];
	Player * myPlayer_;

public:
};

#endif
