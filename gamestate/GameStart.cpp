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


