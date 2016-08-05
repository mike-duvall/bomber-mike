#ifndef VICTORY_LIGHT_H
#define VICTORY_LIGHT_H

#include "GameObject.h"

class BlitterObject;


#include <ddraw.h> 
#include <vector>

using namespace std;


class VictoryLight;

#define VICTORY_LIGHT_COLOR_BLUE 0 
#define VICTORY_LIGHT_COLOR_RED  1 
#define VICTORY_LIGHT_COLOR_GREEN 2 
#define VICTORY_LIGHT_COLOR_ORANGE 3 

typedef vector<VictoryLight *> VICTORY_LIGHT_VECTOR;

class VictoryLight : public GameObject
{
public:
	VictoryLight(int x, int y, int color);


	void Update();

private:


	int countdownTimer;
	int countdownTimerInitialValue;


	static BlitterObject * theBlueArchetypeBlitterObject_;
	static BlitterObject * theRedArchetypeBlitterObject_;
	static BlitterObject * theGreenArchetypeBlitterObject_;
	static BlitterObject * theOrangeArchetypeBlitterObject_;
	void SetupArchetypes();


};

#endif
