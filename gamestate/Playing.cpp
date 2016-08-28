#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/SimpleGameObject.h"


#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"

#include <iostream>
#include <sstream>
using namespace std;


Playing::Playing()
{

}


Playing::~Playing()
{
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





void Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Update_And_Draw_Players();

	DDraw_Flip();


}
