#ifndef END_OF_ROUND_REPORT_H
#define END_OF_ROUND_REPORT_H



#include "GameState.h"


#include "../gameobjects/VictoryLightHorizontalGroup.h"
#include "../gameobjects/SimpleGameObject.h"




class EndOfRoundReport : public GameState
{
public:

	EndOfRoundReport();
	GameState * Update();

private:

	void Update_And_Draw_VictoryLights();
	void Create_Horizontol_Groups();
	void Create_Vertical_Groups();
	void Create_Title();
	void Create_PlayerIcons();
	void Create_Player_GoldCoins();
	void Draw_GoldCoins();

	int countdownTimer;
	VICTORY_LIGHT_HORIZONTAL_GROUP_VECTOR victoryLightHorizontalGroups;
	SimpleGameObject * winMatchText;
	SimpleGameObject * winMatchNumber;

	SIMPLE_GAME_OBJECT_VECTOR_VECTOR playerWinGoldCoinsVector;


	SIMPLE_GAME_OBJECT_VECTOR playerIcons;



};

#endif
