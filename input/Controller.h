
#ifndef CONTROLLER_H
#define CONTROLLER_H



class Controller
{
public:
	virtual int GetControlEvent() = 0;
	virtual bool IsDropBombPressed() = 0;


public:
};

#endif


