#ifndef SELECTING_CONTROLLER_H
#define SELECTING_CONTROLLER_H



#include "GameState.h"



#include "../gameobjects/ControllerSelector.h"

class SelectingController : public GameState

{
public:


	SelectingController();

private:

	GameState * Update();
	

};

#endif
