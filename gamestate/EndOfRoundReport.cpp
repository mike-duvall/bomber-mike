#include "EndOfRoundReport.h"



#include "../t3dlib/t3dlib1.h"
#include "../universe/Universe.h"
#include "../input/Keyboard.h"
#include "../gameobjects/SimpleGameObject.h"

#include "GameStart.h"


#include <iostream>
#include <sstream>
using namespace std;

extern void Draw_Score(Player * aPlayer, int x, int y);



EndOfRoundReport::EndOfRoundReport()
{
	
 	countdownTimer = 150;
//	countdownTimer = 700;
	Create_Horizontol_Groups();
	Create_Vertical_Groups();
	Create_Title();
	Create_PlayerIcons();
	Create_Player_GoldCoins();
	
}


void EndOfRoundReport::Create_Player_GoldCoins()
{


	int y = 115;
	int yIncrement = 60;

 	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		SIMPLE_GAME_OBJECT_VECTOR * nextGoldCoinVector = new SIMPLE_GAME_OBJECT_VECTOR;
		playerWinGoldCoinsVector.push_back(nextGoldCoinVector);

		int x = 170;
		int xIncrement = 65;
		int numberOfWins = next->GetNumberOfWins();
		for(int i = 0; i < numberOfWins; i++)
		{
			SimpleGameObject * goldCoin  = new SimpleGameObject(x,y,44,44,"bitmaps/EndOfRound/GoldCoin.bmp");
			nextGoldCoinVector->push_back(goldCoin);
			x += xIncrement;
		}

		y += yIncrement;
	}


}


string GetBitmapFileNameFromPlayerType(Player * aPlayer, bool isSurvivor)
{
	string bitmapFilename = "bitmaps/EndOfRound/";

	bitmapFilename = bitmapFilename + aPlayer->GetNameFromPlayerType();
	bitmapFilename = bitmapFilename + "Player";
	if(isSurvivor)
	{
		bitmapFilename = bitmapFilename + "Win.bmp";
	}
	else
	{
		bitmapFilename = bitmapFilename + "Lose.bmp";
	}

	return bitmapFilename;
}


void EndOfRoundReport::Create_PlayerIcons()
{

	int x = 70;
	int y = 115;
	int yIncrement = 60;

 	Player * survivor = Universe::GetSurvivingPlayer();

	PLAYER_VECTOR::iterator theIterator;

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{

		Player * next = *theIterator;
		int playerType = next->GetPlayerType();
		bool isSurvivor = (survivor == next);
		string bitmapFileName = GetBitmapFileNameFromPlayerType(next, isSurvivor);

		SimpleGameObject * nextIcon = new SimpleGameObject(x,y,80,38,bitmapFileName,1);
		playerIcons.push_back(nextIcon);
		y += yIncrement;

	}






}


void EndOfRoundReport::Create_Title()
{

	winMatchText = new SimpleGameObject(200,60,238,32,"bitmaps/EndOfRound/WinMatch.bmp");
	int numberOfRounds = Universe::GetNumberOfRoundsInGame();

	int numberX = 150;
	int numberY = 63;

	DWORD mask = _RGB32BIT(0,36,146,255);

	switch(numberOfRounds)
	{

	case 1:
		winMatchNumber = new SimpleGameObject(numberX,numberY,16,30,"bitmaps/GameStart/1.bmp", mask);
		break;

	case 2:
		winMatchNumber = new SimpleGameObject(numberX,numberY,24,30,"bitmaps/GameStart/2.bmp", mask);
		break;

	case 3:
		winMatchNumber = new SimpleGameObject(numberX,numberY,24,30,"bitmaps/GameStart/3.bmp", mask);
		break;

	case 4:
		winMatchNumber = new SimpleGameObject(numberX,numberY,24,30,"bitmaps/GameStart/4.bmp", mask);
		break;

	case 5:
		winMatchNumber = new SimpleGameObject(numberX,numberY,22,30,"bitmaps/GameStart/5.bmp", mask);
		break;

	}



}

void EndOfRoundReport::Create_Vertical_Groups()
{


}


void EndOfRoundReport::Create_Horizontol_Groups()
{


}



void EndOfRoundReport::Draw_GoldCoins()
{

	SIMPLE_GAME_OBJECT_VECTOR_VECTOR::iterator theIterator;

	for( theIterator = playerWinGoldCoinsVector.begin();
		 theIterator != playerWinGoldCoinsVector.end();
		 theIterator++)
	{

		SIMPLE_GAME_OBJECT_VECTOR * nextGoldCoinVector = *theIterator;

		SIMPLE_GAME_OBJECT_VECTOR::iterator innerIter;;

		for( innerIter = nextGoldCoinVector->begin();
			 innerIter != nextGoldCoinVector->end();
			 innerIter++)
		{
			SimpleGameObject * nextCoin = (SimpleGameObject *) *innerIter;
			nextCoin->Draw(lpddsback);

		}

	}

}






GameState * EndOfRoundReport::Update()
{

	DWORD backgroundColor = _RGB32BIT(0,34,146,255);

	int matchOver = 0;
 	Player * survivor = Universe::GetSurvivingPlayer();



	if(survivor)
	{
		if( survivor->GetNumberOfWins() == Universe::GetNumberOfRoundsInGame())
		{

			matchOver = 1;
		}
	}


	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Draw_GoldCoins();

	winMatchText->Draw(lpddsback);
	winMatchNumber->Draw(lpddsback);
	SIMPLE_GAME_OBJECT_VECTOR::iterator theIterator;

	for(	theIterator = playerIcons.begin();
		theIterator != playerIcons.end();
		theIterator++
		)
	{

		SimpleGameObject * next = *theIterator;
		next->Draw(lpddsback);
	}

	DDraw_Flip();

	countdownTimer--;

	if(countdownTimer <= 0)
	{
		return new GameStart();
	}

	return this;

}


