#ifndef VICTORY_LIGHT_VERTICAL_GROUP_H
#define VICTORY_LIGHT_VERTICAL_GROUP_H


#include "GameObject.h"

class BlitterObject;

#include <ddraw.h> 
#include <vector>

using namespace std;

class VictoryLight;

class VictoryLightVerticalGroup;

typedef vector<VictoryLightVerticalGroup *> VICTORY_LIGHT_VERTICAL_GROUP_VECTOR;

class VictoryLightVerticalGroup  : public GameObject
{
public:
	VictoryLightVerticalGroup(int x, int y);
	virtual ~VictoryLightVerticalGroup();

	void Update();
	void Draw(LPDIRECTDRAWSURFACE7 dest);

protected:


	VictoryLight * blueLight;
	VictoryLight * redLight;
	VictoryLight * greenLight;
	VictoryLight * orangeLight;
	VictoryLight * bottomBlueLight;


};

#endif
