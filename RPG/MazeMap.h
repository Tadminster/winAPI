#pragma once
#include "framework.h"
#include "BattleSystem.h"
#include "Player.h"
#include "Monster.h"
#include "Trade.h"
#include "ioSystem.h"

class MazeMap
{
private:
	int cols;
	int rows;

	std::string** map;

public:
	/* 배열의 세로크기, 가로크기*/
	MazeMap(int c, int r);
	~MazeMap();

	void			startMapEvent(std::string& next_room, class RPG_Player* player);
	void			enterQuestionMark(class RPG_Player* player);

	void			room_Trap(class RPG_Player* player, int playerInput);
	void			room_FountainOfRecovery(class RPG_Player* player);
	void			room_NormalChest(class RPG_Player* player, int playerInput);
	void			room_RareChest(class RPG_Player* player);

	/* 전투 시작 
	* param1 플레이어, 
	* param2 1=랜덤일반, 2=미믹, 9=보스) 
	*/
	void			battleEvent(class RPG_Player* player, int monsterType);

	std::string&	getMap(int y, int x);
	/* 맵사이즈 가져오기 (col==0, row==1) */
	int				getMapSize(int arrow);

	void			setMapElement(int y, int x, std::string mapData);

	void			createMap();
	void			printMap(class RPG_Player* player);
	void			swapMap(int playerY, int playerX, int targetY, int targetX);
};

