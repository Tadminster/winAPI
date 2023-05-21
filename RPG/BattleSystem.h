#pragma once
#include "framework.h"
#include "Player.h"
#include "Monster.h"


class BattleSystem
{
private:
	class RPG_Player* player;
	class Monster* monster;

public:
	BattleSystem(class RPG_Player* player);

	void		setEnemy(class Monster* monster);
	
	void		startBattle();
};

