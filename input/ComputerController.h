#ifndef COMPUTER_CONTROLLER_H
#define COMPUTER_CONTROLLER_H


#include "Controller.h"

class Player;
class Bomb;
class ExplosionPart;
class GameObject;
class _asNode;



class ComputerController : public Controller
{
public:
 	ComputerController(Player * aPlayer);
 	virtual ~ComputerController();
 
 	int GetControlEvent();
 	bool IsDropBombPressed();
	Player * GetSelectedEnemy() { return selectedEnemy; }


private:
	int PursueEnemy();


	int guidanceCountdownTimer;

	void DrawBoundingBox( _asNode * node );
	int CalculateDistanceToPlayer(Player * anEnemyPlayer);
	float DistanceBetweenTwoPoints(int x1, int y1, int x2, int y2 );
	int RunFromBomb(Bomb * aBomb);
	int HandleStandingOnBomb();
	int HandleSameRowAsBomb();
	int HandleSameColumnAsBomb();
	Bomb * GetBombCloseToMe();
	ExplosionPart * GetExplosionPartCloseToMe();
	Player * ChooseNextEnemy();
	int GetNumberOfAlivePlayers();
	GameObject * GetGameObjectAtPoint( int x, int y);
	int lastControlEvent;
	int lastX;
	int lastY;
	Player * myPlayer;
	int comparisonOrder;

	Player * selectedEnemy;
	

	int previousBestNodeX;
	int previousBestNodeY;

};

#endif
