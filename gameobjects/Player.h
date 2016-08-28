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

	// case 1 
	bool PlayerLeftEdgeOverlapsWithRightHalfOfBlock(Block * aBlock);
	void HandleMoveDownLeftEdgeOverRightHalf();

	// cases 2 & 3
	bool PlayerLeftEdgeOverlapsWithLeftHalfOfBlock(Block * aBlock);
	void HandleMoveUpOrDownLeftEdgeOverLeftHalf();

	// case 4
	bool PlayerDirectlyAboveOrBelowBlock(Block * aBlock);
	void HandleBlockedMoveDown();


	// cases 5 & 6
	bool PlayerRightEdgeOverlapsWithRightHalfOfBlock(Block * aBlock);
	void HandleMoveUpOrDownRightEdgeOverRightHalf();


	// case 7
	bool PlayerRightEdgeOverlapsWithLeftHalfOfBlock(Block * aBlock);
	void HandleMoveDownRightEdgeOverLeftHalf();
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	void HandleMoveUp();
	void HandleMoveUpWithNoBlockAbove();
	void HandleMoveUpWithBlockAbove(Block * aBlock);
	GameObject *  GetBlockingGameObjectImmediatelyAboveAndToTheRight();
	GameObject *  GetBlockingGameObjectImmediatelyAboveAndToTheLeft();

	// case 1 
	void HandleMoveUpPlayerLeftEdgeOverlapsBlockRightHalf();

	// cases 2 & 3
	//	uses void HandleMoveUpOrDownLeftEdgeOverLeftHalf();
		 
	// case 4
	void HandleBlockedMoveUp();
// 
	// cases 5 & 6
//	uses 	void HandleMoveUpOrDownRightEdgeOverRightHalf();

// 	// case 7
 	void HandleMoveUpPlayerRightEdgeOverlapsLeftHalf();
	//////////////////////////////////////////////////


	//////////////////////////////////////////////////
//	bool HandleMoveRight();
	GameObject *  GetBlockingGameObjectImmediatelyToTheRightAndAbove();
	GameObject *  GetBlockingGameObjectImmediatelyToTheRightAndBelow();

	void HandleMoveRightWithNoBlockToTheRight();
	bool HandleMoveRightWithBlockToTheRight(Block * aBlock);


 	// case 1 
	bool PlayerBottomEdgeOverlapsWithTopHalfOfBlock(Block * aBlock);
	void HandleMoveRightBottomEdgeOverlapsTopHalf();

 	// cases 2 & 3
	bool PlayerBottomEdgeOverlapsWithBottomHalfOfBlock(Block * aBlock);
	void HandleMoveRightOrLeftWithBottomEdgeOverlappingBottomeHalf();

 	// case 4
	bool PlayerDirectlyToLeftOrRightOfBlock(Block * aBlock);
	void HandleBlockedMoveRight();

 	// cases 5 & 6
	bool PlayerTopEdgeOverlapsWithTopHalfOfBlock(Block * aBlock);
	void HandleMoveRightOrLeftTopEdgeOverlappingTopHalf();

 	// case 7
	bool PlayerTopEdgeOverlapsWithBottomHalfOfBlock(Block * aBlock);
	void HandleMoveRightTopEdgeOverlappingBottomHalf();
	//////////////////////////////////////////////////



	//////////////////////////////////////////////////
	void HandleMoveLeftWithNoBlockToTheLeft();
	bool HandleMoveLeftWithBlockToTheLeft(Block * aBlock);
	GameObject *  GetBlockingGameObjectImmediatelyToTheLeftAndAbove();
	GameObject *  GetBlockingGameObjectImmediatelyToTheLeftAndBelow();


	// case 1 
	void HandleMoveLeftBottomEdgeOverlapsTopHalf();


	// cases 2 & 3
	//	uses void HandleMoveRightOrLeftWithBottomEdgeOverlappingBottomeHalf();

 	// case 4
	void HandleBlockedMoveLeft();

 	// cases 5 & 6
 	//	uses 	void HandleMoveUpOrDownRightEdgeOverRightHalf();
 
// 	// 	// case 7
	void HandleMoveLeftTopEdgeOverlappingBottomHalf();



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
