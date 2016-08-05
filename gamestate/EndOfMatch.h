#ifndef END_OF_MATCH_H
#define END_OF_MATCH_H



#include "GameState.h"


class EndOfMatch : public GameState
{
public:

	EndOfMatch() { countdownTimer = 400;}
	GameState * Update();

private:

	int countdownTimer;


};

#endif
