#ifndef SELECTING_CONTROLLER_H
#define SELECTING_CONTROLLER_H



#include "GameState.h"
#include "../gameobjects/Selector.h"
#include "../fmod//fmod.hpp"
#include "SelectingBaseGameState.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../gameobjects/ControllerSelector.h"

class SelectingController : public SelectingBaseGameState
{
public:


	SelectingController( FMOD::Channel * aSoundChannel);
//	SelectingController();

private:

	virtual bool HandleKeyboardInput();

	GameState * OnItemSelected();
	GameState * Update();
	GameState * GetNextGameStateAndDeleteCurrentGameState();
	void Create_PlayerIcons();

	void Draw_PlayerIcons();
	void Draw_BomberIcons();
	void Draw_ControllerSelectors();

	void HandleIncrementSelectedController();
	void HandleDecrementSelectedController();

	void Create_IconsForPlayer(const string & playerNumber, int x, int y);

	virtual void Draw_Special();
	FMOD::Channel * soundChannel;

	SIMPLE_GAME_OBJECT_VECTOR playerIcons;
	SIMPLE_GAME_OBJECT_VECTOR bomberIcons;
	CONTROLLER_SELECT_VECTOR controllerSelectors;

};

#endif
