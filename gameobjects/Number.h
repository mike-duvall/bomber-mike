#ifndef NUMBER_H
#define NUMBER_H


#include "GameObject.h"




class Number  : public GameObject
{
public:
	Number(int x, int y);
	void SetValue(int aValue);
	int GetValue();


protected:

//	int value;
//	SimpleGameObject * numberSimpleObject;


public:
};

#endif
