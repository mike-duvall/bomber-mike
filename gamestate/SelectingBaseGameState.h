#ifndef SELECTING_BASE_GAMESTATE_H
#define SELECTING_BASE_GAMESTATE_H



#include "GameState.h"
//#include "../gameobjects/SelectMatch.h"

class GameObject;
class SimpleGameObject;
class Selector;



class SelectingBaseGameState : public GameState
{
public:


	SelectingBaseGameState();
	GameState * Update();


protected:

	virtual GameState * OnItemSelected() = 0;
	void HandleSetupPlayers(int numPlayers);
	void UpdateSelectorLocation();
	virtual bool HandleKeyboardInput();
	virtual bool HandleJoystickInput();

	void HandleMoveSelectorUp();
	void HandleMoveSelectorDown();

	virtual void Draw_Special() {};



	GameObject * gameObject;
	Selector * selector;
	int pauseAfterSelectionTimer;
	int selectorPosition;
	int selectorX;
	int selectorY;
	int selectorYBase;
	int maxSelectorPosition;
	int selectorYIncrement;


	bool keyRecentlyPressed;
	int keyPresseedCountdownTimer;
	int keyPressedCountdownInitialValue;

	int subState;


};

#endif
