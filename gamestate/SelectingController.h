#ifndef SELECTING_CONTROLLER_H
#define SELECTING_CONTROLLER_H



#include "GameState.h"
#include "../gameobjects/Selector.h"
#include "SelectingBaseGameState.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../gameobjects/ControllerSelector.h"

class SelectingController : public SelectingBaseGameState
{
public:


	SelectingController();

private:

	GameState * OnItemSelected();
	GameState * Update();
	GameState * GetNextGameStateAndDeleteCurrentGameState();
	
	SIMPLE_GAME_OBJECT_VECTOR playerIcons;
	SIMPLE_GAME_OBJECT_VECTOR bomberIcons;
	CONTROLLER_SELECT_VECTOR controllerSelectors;

};

#endif
