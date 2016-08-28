#ifndef PLAYER_H
#define PLAYER_H


#include <ddraw.h> 
#include "../t3dlib/t3dlib1.h"


class BlitterObject;


#include <vector>

using namespace std;

class Controller;

#define WHITE_PLAYER 1




class Player 
{
public:
	Player();
	Player(int x, int y);
	void SetController(Controller * aController) { this->theController = aController;}
	void Update(int controlEvent);
	bool Update();
	void Draw(LPDIRECTDRAWSURFACE7 dest);

	void SetInitialValuesForNewRound();

	BlitterObject * GetBlitterObject() { return theBlitterObject_; }
	virtual ~Player();


private:

	Controller * theController;

	//////////////////////////////////////////////////
	void HandleMoveDown();
	void HandleMoveUp();
	void HandleMoveLeft(int controlEvent);
	bool HandleMoveRight(int controlEvent);
	//////////////////////////////////////////////////

	int moveIncrementAmount;
	int initialX;
	int initialY;


protected:

	BlitterObject * theBlitterObject_;

};

#endif
