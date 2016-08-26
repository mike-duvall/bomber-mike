#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/Block.h"
#include "../gameobjects/ExplosionPart.h"
#include "../gameobjects/ExplodingPlayer.h"
#include "../gameobjects/SimpleGameObject.h"
#include "../gameobjects/Timer.h"
#include "../gameobjects/Number.h"


#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"
#include "../gamestate/EndOfRound.h"

#include <iostream>
#include <sstream>
using namespace std;

#include "../sound/MSound.h"

// Dummy change

Playing::Playing()
{
	soundChannel = Sound::PlaySound(Sound::playing, .5f);
// 	clock = new SimpleGameObject(30,10,30,40,"bitmaps/InGame/Scoreboard/Clock.bmp",_RGB32BIT(0,0,182,0));
// 	timer = new Timer(70,25);
	clock = new SimpleGameObject(10,-40,30,40,"bitmaps/InGame/Scoreboard/Clock.bmp",_RGB32BIT(0,0,182,0));
	timer = new Timer(50,-25);

	SetScoreIconLocations();


}


void Playing::SetScoreIconLocations()
{
	PLAYER_VECTOR::iterator theIterator;

	int playerIndex = 0;


	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;

		int playerType = next->GetPlayerType();
		int x = 135 + (playerType * 65) - 20;
		int y = 15 - 50;

		next->SetScoreIconPos(x,y);
//		next->GetScoreIcon()->GetBlitterObject()->Set_Pos(x,y);
		next->GetScoreShell()->GetBlitterObject()->Set_Pos(x + 40,y + 5);
		next->GetScoreNumber()->GetBlitterObject()->Set_Pos(x + 40, y + 5);

	}

}

Playing::~Playing()
{
	soundChannel->stop();
}







void Update_And_Draw_Players()
{

	PLAYER_VECTOR::iterator theIterator;

	int playerIndex = 0;
	

	for(	theIterator = Universe::GetPlayers().begin();
		theIterator != Universe::GetPlayers().end();
		theIterator++
		)
	{
		Player * next = *theIterator;
		playerIndex++;

		if(next->GetPlayerState() == PLAYER_STATE_ALIVE)
		{
			boolean removeThisPlayer =  next->Update();
			next->Draw(lpddsback);

		}
	}

}





GameState * Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Update_And_Draw_Players();

	DDraw_Flip();

	return this;

}
