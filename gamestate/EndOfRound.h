#ifndef END_OF_ROUND_H
#define END_OF_ROUND_H



#include "GameState.h"


class EndOfRound : public GameState
{
public:


	EndOfRound() { countDownTimer = 150;}
	GameState * Update();

private:

	int countDownTimer;
};

#endif
