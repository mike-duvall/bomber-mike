#include <gmock/gmock.h>  // Brings in Google Mock.

#include "player.h"

class MockPlayer : public Player {

public:
//	MockPlayer(int y, int s) : Player(x,y,s) {};
//	MOCK_METHOD3(MockPlayer, void(int,int,int));
	//	MOCK_METHOD0(PenUp, void());
	//MOCK_METHOD0(PenDown, void());
	MOCK_METHOD0(GetExplosionSize,  int()   );
	//MOCK_METHOD1(Forward, void(int distance));
	//MOCK_METHOD1(Turn, void(int degrees));
	//MOCK_METHOD2(GoTo, void(int x, int y));
	//MOCK_CONST_METHOD0(GetX, int());
	//MOCK_CONST_METHOD0(GetY, int());
};