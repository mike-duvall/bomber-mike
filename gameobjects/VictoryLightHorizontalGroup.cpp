#include "VictoryLightHorizontalGroup.h"




#include "../gameobjects/VictoryLight.h"



VictoryLightHorizontalGroup::VictoryLightHorizontalGroup(int x, int y)
{
	int animations[] = { 0,1,0,1 };

	int widthOffset = 15;
	
	blueLight = new VictoryLight(x,y,VICTORY_LIGHT_COLOR_BLUE);
	redLight = new VictoryLight(x + widthOffset,y,VICTORY_LIGHT_COLOR_RED);
	greenLight = new VictoryLight(x+ (2 * widthOffset),y,VICTORY_LIGHT_COLOR_GREEN);
	orangeLight = new VictoryLight(x+ (3 * widthOffset),y,VICTORY_LIGHT_COLOR_ORANGE);




}


VictoryLightHorizontalGroup::~VictoryLightHorizontalGroup()
{
}





void VictoryLightHorizontalGroup::Update()
{

	blueLight->Update();
	redLight->Update();
	greenLight->Update();
	orangeLight->Update();

}

void VictoryLightHorizontalGroup::Draw(LPDIRECTDRAWSURFACE7 dest)
{

	blueLight->Draw(dest);
	redLight->Draw(dest);
	greenLight->Draw(dest);
	orangeLight->Draw(dest);

}


