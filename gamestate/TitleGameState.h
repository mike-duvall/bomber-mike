#ifndef TITLE_GAMESTATE_H
#define TITLE_GAMESTATE_H



#include "GameState.h"
#include "../sound/MSound.h"

class SimpleGameObject;


#define SUB_STATE_BLACK_MOVING  0
#define SUB_STATE_WHITE_MOVING  1
#define SUB_STATE_TITLE_MOVING  2
#define SUB_STATE_ANIMATING_CREDITS  3
#define SUB_STATE_ANIMATING_FASHIZZLE  4
#define SUB_STATE_DISPLAYING_MENU   5


class TitleGameState : public GameState
{
public:


	TitleGameState();
	~TitleGameState();
	GameState * Update();

private:


	int subState;
	void HandleBlackMoving();
	void HandleWhiteMoving();
	void HandleTitleMoving();
	void HandleDisplayingMenu();
	void HandleAnimatingCredits();
	void HandleAnimatingFashizzle();
	
	int blackBombermanTimer;
	SimpleGameObject * blackPlayer;

	int whiteBombermanStartTimer;
	int whiteBombermanTimer;
	int titleMovingTimer;
	SimpleGameObject * whitePlayer;


	SimpleGameObject * title;
	int titleX;
	int titleY;

	SimpleGameObject * bomberTitle;
	SimpleGameObject * manTitle;
	SimpleGameObject * yearTitle;
	SimpleGameObject * clonedBy;
	SimpleGameObject * mikeDuVall;
	SimpleGameObject * fashizzle;
	SimpleGameObject * pushButton;

	int waitForCreditsTimer;
	int cloneByTimer;
	int preDuVallTimer;
	int mikeDuVallTimer;
	int preFashizzleCountdownTimer;

	FMOD::Channel * openingChannel;


};

#endif
