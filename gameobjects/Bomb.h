#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class Bomb;
class Player;
class Point;

typedef vector<Bomb *> BOMB_VECTOR;
typedef vector<Point> POINT_VECTOR;


class Bomb : public GameObject
{
public:
	Bomb(int x, int y,Player * aPlayer);
	virtual ~Bomb();

	bool Update();
	bool IsPointInBomb(int x, int y);
	bool IsPlayerMovingOverAfterDropping(Player * aPlayer);
	bool HasPlayerLeft() { return this->hasPlayerLeft_;};
	void AddExplosionParts();
	void AddFlames(int explosionSize, int xModifier, int yModifier, int type);
	Player * GetPlayer() { return myPlayer_;}
	POINT_VECTOR GetPredictedFlameLocations();
private:

	int coundownTimer_;
	bool hasPlayerLeft_;
	Player * myPlayer_;


	static BlitterObject * theArchetypeBlitterObject_;
	void SetupArchetype();
	void AddFlamePredictedPoints(int explosionSize, int xModifier, int yModifier, POINT_VECTOR & pointVector);

};

#endif
