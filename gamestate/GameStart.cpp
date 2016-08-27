#include "GameStart.h"


#include "Playing.h"

#include "../t3dlib/t3dlib1.h"


#include "../gameobjects/Player.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"
#include <stdio.h>
#include "Playing.h"



GameStart::GameStart()
{


	numberOfPlayers = (int)Universe::GetPlayers().size();
	numberOfRounds = Universe::GetNumberOfRoundsInGame();
	countdownTimer = 250;
	gameStartFlashTimeInitValue = 15;
	gameStartFlashTimer = gameStartFlashTimeInitValue;
	isDrawingGameStart = true;;

	setupCalled = 0;

	DWORD mask = _RGB32BIT(0,36,146,255);
	gameStartGameObject = new SimpleGameObject(150,350,332,60,"bitmaps/GameStart/GameStart.bmp",mask);
	winMatchGameObject = new SimpleGameObject(200,75,238,30,"bitmaps/GameStart/WinMatch.bmp",mask);

	_1GameObject = new SimpleGameObject(140,75,16,30,"bitmaps/GameStart/1.bmp", mask);
	_2GameObject = new SimpleGameObject(140,75,24,30,"bitmaps/GameStart/2.bmp", mask);
	_3GameObject = new SimpleGameObject(140,75,24,30,"bitmaps/GameStart/3.bmp", mask);
	_4GameObject = new SimpleGameObject(140,75,24,30,"bitmaps/GameStart/4.bmp", mask);
	_5GameObject = new SimpleGameObject(140,75,22,30,"bitmaps/GameStart/5.bmp", mask);


	int padWidth = 84;
	int padHeight = 74;
	int padLeftX = 140;
	int padRightX = 380;
	int padUpperY = 125;
	int padLowerY = 255;
 	whitePad1GameObject = new SimpleGameObject(padLeftX,padUpperY,padWidth,padHeight,"bitmaps/GameStart/WhitePad1.bmp", mask );
 	blackPad2GameObject = new SimpleGameObject(padRightX,padLowerY,padWidth,padHeight,"bitmaps/GameStart/BlackPad2.bmp", mask );

  	redPad3GameObject = new SimpleGameObject(padRightX,padUpperY,padWidth,padHeight,"bitmaps/GameStart/RedPad3.bmp", mask );
  	bluePad4GameObject = new SimpleGameObject(padLeftX,padLowerY,padWidth,padHeight,"bitmaps/GameStart/BluePad4.bmp", mask );

}

void Setup()
{

 	Universe::SetMapLeftX(20);
 	Universe::SetMapTopY(50);


	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		next->SetInitialValuesForNewRound();
	}


	Universe::ClearAndDeleteAll();


}

GameState * GameStart::Update()
{

	Setup();
    delete this;
	return new Playing();
}


