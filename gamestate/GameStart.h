#ifndef GAMESTART_H
#define GAMESTART_H



#include "GameState.h"



class SimpleGameObject;

class GameStart : public GameState
{
public:

	GameStart();
	GameState * Update();

private:

	int numberOfPlayers;
	int numberOfRounds;
	int countdownTimer;
	int gameStartFlashTimer;
	int gameStartFlashTimeInitValue;
	bool isDrawingGameStart;
	int setupCalled;
	SimpleGameObject * gameStartGameObject;
	SimpleGameObject * winMatchGameObject;
	SimpleGameObject * _1GameObject;
	SimpleGameObject * _2GameObject;
	SimpleGameObject * _3GameObject;
	SimpleGameObject * _4GameObject;
	SimpleGameObject * _5GameObject;
	SimpleGameObject * whitePad1GameObject;
	SimpleGameObject * blackPad2GameObject;
	SimpleGameObject * redPad3GameObject;
	SimpleGameObject * bluePad4GameObject;


};

#endif
