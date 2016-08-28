#ifndef PLAYER_H
#define PLAYER_H


#include <ddraw.h> 
#include "../t3dlib/t3dlib1.h"
#include "GameObject.h"

class BlitterObject;
class IndestructableBlock;
class Block;


#include <vector>

using namespace std;


class Player;
class Joystick;
class Powerup;
class SimpleGameObject;
class Number;
class Controller;

typedef vector<Player *> PLAYER_VECTOR;



#define WHITE_PLAYER 1
#define BLACK_PLAYER 2
#define RED_PLAYER   3
#define BLUE_PLAYER  4


#define PLAYER_STATE_ALIVE 1
#define PLAYER_STATE_DEAD  2



class Player : public GameObject
{
public:
	Player();
	Player(int x, int y, int playerType);
	void SetController(Controller * aController) { this->theController = aController;}
	void Update(int controlEvent);
	bool Update();
	void Draw(LPDIRECTDRAWSURFACE7 dest);

	string GetNameFromPlayerType();

	void IncrementNumberOfAllowedBombs() { this->numAllowedBombs++;}
	void DecrementNumberOfActuallyDroppedBombs() { this->numBombsDropped--;}
	void SetExplosionSize(int newExplosionSize) { explosionSize = newExplosionSize;}
	virtual int  GetExplosionSize() { return explosionSize; }
	int GetPlayerState() { return playerState;}
	int GetPlayerType() { return playerType;}
	int GetNumberOfWins() { return numberOfWins;}
	void SetNumberofWins(int numWins) { numberOfWins = numWins;}
	void SetInitialValuesForNewMatch();
	void SetInitialValuesForNewRound();
	const string & GetName() { return name;}

	SimpleGameObject * GetScoreShell() { return scoreShell; }


private:

	string GetBitmapFilenameFromPlayerType(int aPlayerType);


	Controller * theController;

	//////////////////////////////////////////////////
	void HandleMoveDown();
	void HandleMoveUp();
	void HandleMoveLeft(int controlEvent);
	bool HandleMoveRight(int controlEvent);
	//////////////////////////////////////////////////

	int bombDropCoundownTimer;
	int bombDropCoundownTimerInitialValue;
	int numAllowedBombs;
	int numBombsDropped;
	int explosionSize;
	int moveIncrementAmount;
	int playerState;
	int playerType;
	int numberOfWins;
	int initialX;
	int initialY;
	string name;

	BOB * theCollisionBOB_;

	SimpleGameObject * scoreIcon;
	SimpleGameObject * scoreCryIcon;
	SimpleGameObject * scoreShell;
	Number * scoreNumber;


};

#endif
