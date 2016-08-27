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


#include "../gameobjects/Bomb.h"
#include "../gameobjects/Player.h"
#include "../gameobjects/ExplodingPlayer.h"



class Universe
{
public:



	static int GetMapLeftX() { return mapLeftX;}
	static int GetMapTopY() { return mapTopY;}
	static void SetMapLeftX(int newX) { mapLeftX = newX;}
	static void SetMapTopY(int newY) { mapTopY = newY;}

	static PLAYER_VECTOR & GetPlayers() { return players; }
	static int GetNumberOfAlivePlayers();
	static Player * GetSurvivingPlayer();

	static EXPLODING_PLAYER_VECTOR & GetExplodingPlayers() { return explodingPlayers; }

	static Block * GetBlockAtPoint(int x, int y);
	static Block * GetBlockAtGridPoint(int x, int y);
	static void RemoveBlock(Block * aBlock);
	static Point GetNearestCenterPointFromPoint(int x, int y);


	static BOMB_VECTOR & GetBombs() { return bombs; }
	static Bomb * Universe::GetBombAtPoint(int x, int y);
	static Bomb * Universe::GetBombAtGridPoint(int x, int y);


	static Keyboard * GetKeyboard() { return keyboard; }
	static void SetKeyboard(Keyboard * aKeyboard ) { keyboard = aKeyboard; }


	static int GetNumberOfRoundsInGame() { return numberOfRoundsInGame; }
	static void SetNumberOfRoundsInGame(int aNumberOfRounds) { numberOfRoundsInGame = aNumberOfRounds;}

	static void ClearAndDeleteAll();


private:


	static int mapLeftX;
	static int mapTopY;

	static BOMB_VECTOR  bombs;
	static PLAYER_VECTOR players;
	static EXPLODING_PLAYER_VECTOR explodingPlayers;


	static Keyboard * keyboard;
	static Joystick * joystick;

	static int numberOfRoundsInGame;


};

#endif
