#ifndef CONTROLLER_SELECTOR_H
#define CONTROLLER_SELECTOR_H


class BlitterObject;

#include <ddraw.h> 
#include <vector>
#include "GameObject.h"

using namespace std;

class SimpleGameObject;
class ControllerSelector;

typedef vector<ControllerSelector *> CONTROLLER_SELECT_VECTOR;

#define CONTROLLER_COMPUTER 1
#define CONTROLLER_GAMEPAD  2
#define CONTROLLER_KEYBOARD 3



class ControllerSelector
{
public:
	
	ControllerSelector(int x, int y);
	virtual ~ControllerSelector();
	void Draw(LPDIRECTDRAWSURFACE7 dest);
	void SetSelection(int newSelection) { selection = newSelection;}
	int GetSelection() { return selection;}


private:

	int selection;
	SimpleGameObject * computerSelection;
	SimpleGameObject * gamepadSelection;
	SimpleGameObject * keyboardSelection;



};

#endif
