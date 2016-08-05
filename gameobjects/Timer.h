#ifndef TIMER_H
#define TIMER_H

#include "GameObject.h"

class BlitterObject;


class SimpleGameObject;
class Number;


class Timer : public GameObject
{
public:
	Timer(int x, int y);

	void Draw(LPDIRECTDRAWSURFACE7 dest);
	void Update();
	boolean Expired();


private:

	bool hasExpired;
	int countdownInterval;
	int countdownIntervalInitialValue;


	SimpleGameObject * emptyTimerShell;
	Number * minutes;
	Number * tensOfSeconds;
	Number * seconds;



};

#endif
