#ifndef EXPLODINGPLAYER_H
#define EXPLODINGPLAYER_H


#include <ddraw.h> 
#include "../t3dlib/t3dlib1.h"
#include "GameObject.h"

class BlitterObject;
class IndestructableBlock;
class Block;


#include <vector>

using namespace std;


class ExplodingPlayer;


#define EXPLODING_PLAYER_STATE_WIGGLING 1
#define EXPLODING_PLAYER_STATE_EXPLODING 2

typedef vector<ExplodingPlayer *> EXPLODING_PLAYER_VECTOR;

class ExplodingPlayer : public GameObject
{
public:
	ExplodingPlayer(int x, int y, int aPlayerType );
	bool Update();
// 	void Draw(LPDIRECTDRAWSURFACE7 dest);
// 	virtual ~ExplodingPlayer();
// 
// 	BOB * GetTheCollisionBob();

private:

	int state;
	int wiggleCountdownTimer;
	int wiggleCountdownInitialValue;

	int explosionCountdownTimer;
	int explodionCountdownInitialValue;


};

#endif
