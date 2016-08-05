#include "SelectingNumPlayers.h"

#include "SelectingNumRounds.h"
#include "../universe/Universe.h"
#include "../gameobjects/SimpleGameObject.h"
#include "GameStart.h"


GameState * SelectingNumRounds::Update()
{

	bool skip = false;
	if(skip)
	{
		Universe::SetNumberOfRoundsInGame(2);
		soundChannel->stop();
		delete this;
		return new GameStart();

	}
	else
	{
		return SelectingBaseGameState::Update();
	}


}



SelectingNumRounds::SelectingNumRounds(	FMOD::Channel * aSoundChannel)
{
	int width = 478;
	int height = 370;
	string filename = "../bitmaps/Selecting/SelectMatch.bmp";
	gameObject = new SimpleGameObject(70,55,width, height,filename);

	selectorPosition = 1;
	selectorX = 130;
	selectorYBase = 142;
	maxSelectorPosition = 5;

	int selectorWidth = 46;
	int selectorHeight = 32;

	UpdateSelectorLocation();

	keyRecentlyPressed = true;
	keyPressedCountdownInitialValue = 25;
	keyPresseedCountdownTimer = keyPressedCountdownInitialValue;
	
	soundChannel = aSoundChannel;

}






GameState * SelectingNumRounds::OnItemSelected()
{
	Universe::SetNumberOfRoundsInGame(selectorPosition);
	soundChannel->stop();
	delete this;
	return new GameStart();

}

