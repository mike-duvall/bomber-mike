#ifndef VICTORY_LIGHT_HORIZONTAL_GROUP_H
#define VICTORY_LIGHT_HORIZONTAL_GROUP_H


#include "GameObject.h"

class BlitterObject;

#include <ddraw.h> 
#include <vector>

using namespace std;

class VictoryLight;

class VictoryLightHorizontalGroup;

typedef vector<VictoryLightHorizontalGroup *> VICTORY_LIGHT_HORIZONTAL_GROUP_VECTOR;

class VictoryLightHorizontalGroup  : public GameObject
{
public:
	VictoryLightHorizontalGroup(int x, int y);
	virtual ~VictoryLightHorizontalGroup();

	void Update();
	void Draw(LPDIRECTDRAWSURFACE7 dest);

protected:


	VictoryLight * blueLight;
	VictoryLight * redLight;
	VictoryLight * greenLight;
	VictoryLight * orangeLight;


};

#endif
