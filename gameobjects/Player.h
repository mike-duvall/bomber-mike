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
	Player(int x, int y, int playerType);
	void SetController(Controller * aController) { this->theController = aController;}
	void Update(int controlEvent);
	bool Update();
	void Draw(LPDIRECTDRAWSURFACE7 dest);

	string GetNameFromPlayerType();

	int GetPlayerType() { return playerType;}
	void SetInitialValuesForNewRound();
	const string & GetName() { return name;}

	BlitterObject * GetBlitterObject() { return theBlitterObject_; }
	BOB * GetTheBob();
	virtual ~Player();


private:

	string GetBitmapFilenameFromPlayerType(int aPlayerType);


	Controller * theController;

	//////////////////////////////////////////////////
	void HandleMoveDown();
	void HandleMoveUp();
	void HandleMoveLeft(int controlEvent);
	bool HandleMoveRight(int controlEvent);
	//////////////////////////////////////////////////

	int moveIncrementAmount;
	int playerType;
	int initialX;
	int initialY;
	string name;


protected:

	BlitterObject * theBlitterObject_;



};

#endif
