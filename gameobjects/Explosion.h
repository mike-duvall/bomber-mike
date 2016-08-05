#ifndef EXPLOSION_H
#define EXPLOSION_H


class BlitterObject;


#include <vector>

#include <ddraw.h>

using namespace std;


class Explosion;
class ExplosionPart;
class Block;
class GameObject;

typedef vector<Explosion *> EXPLOSION_VECTOR;

class Explosion
{
public:
//	Explosion(int x, int y);
	virtual ~Explosion();

	bool Update();
	void Draw(LPDIRECTDRAWSURFACE7 lpddsback);

// 	bool IsBlitterObjectInThisExplosion(GameObject * aBlitterObject);
// 	static bool IsBlitterObjectInAnyExplosion(GameObject * aBlitterObject);


private:

	ExplosionPart * theCenterExplosionPart_;
	ExplosionPart * theRightExplosionPart_;
	ExplosionPart * theBottomExplosionPart_;
	ExplosionPart * theLeftExplosionPart_;
	ExplosionPart * theTopExplosionPart_;

	int coundownTimer_;


public:
};

#endif
