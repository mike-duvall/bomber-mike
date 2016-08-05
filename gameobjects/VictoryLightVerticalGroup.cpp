#include "VictoryLightVerticalGroup.h"




#include "../gameobjects/VictoryLight.h"



VictoryLightVerticalGroup::VictoryLightVerticalGroup(int x, int y)
{


	int offset = 15;

	blueLight = new VictoryLight(x,y ,VICTORY_LIGHT_COLOR_BLUE);
	orangeLight = new VictoryLight(x,y + offset,VICTORY_LIGHT_COLOR_ORANGE);
	greenLight = new VictoryLight(x ,y + (2 * offset),VICTORY_LIGHT_COLOR_GREEN);
	redLight = new VictoryLight(x,y+ (3 * offset),VICTORY_LIGHT_COLOR_RED);
	bottomBlueLight = new VictoryLight(x,y+ (4 * offset),VICTORY_LIGHT_COLOR_BLUE);




}


VictoryLightVerticalGroup::~VictoryLightVerticalGroup()
{
}





void VictoryLightVerticalGroup::Update()
{
	blueLight->Update();
	redLight->Update();
	greenLight->Update();
	orangeLight->Update();
	bottomBlueLight->Update();

}

void VictoryLightVerticalGroup::Draw(LPDIRECTDRAWSURFACE7 dest)
{

	blueLight->Draw(dest);
	redLight->Draw(dest);
	greenLight->Draw(dest);
	orangeLight->Draw(dest);
	bottomBlueLight->Draw(dest);

}


