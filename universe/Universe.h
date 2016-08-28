#ifndef UNIVERSE_H
#define UNIVERSE_H


class Player;
class Keyboard;
class Joystick;
class Point;

// #define MAP_LEFT_X 20
// #define MAP_TOP_Y 50
#define MAP_BLOCK_WIDTH 32
#define MAP_BLOCK_HEIGHT 32


#include "../gameobjects/Player.h"



class Universe
{
public:



	static int GetMapLeftX() { return mapLeftX;}
	static int GetMapTopY() { return mapTopY;}
	static void SetMapLeftX(int newX) { mapLeftX = newX;}
	static void SetMapTopY(int newY) { mapTopY = newY;}

	static PLAYER_VECTOR & GetPlayers() { return players; }


	static Keyboard * GetKeyboard() { return keyboard; }
	static void SetKeyboard(Keyboard * aKeyboard ) { keyboard = aKeyboard; }



private:


	static int mapLeftX;
	static int mapTopY;

	static PLAYER_VECTOR players;


	static Keyboard * keyboard;


};

#endif
