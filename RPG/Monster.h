#pragma once
#include "framework.h"

class Monster
{
private:
	int                     maxHP;
	int                     healthPoint;
	int                     damage;
	int                     defence;
	int                     bounty;
	std::string				name;

public:
	/* 이름, 체력, 공격력, 방어력, 현상금*/
	Monster(std::string n, int hp, int dmg, int def, int gold);

	const std::string&  getName();
	int					getGold();
	int					getMaxHp();
	int					getHp();
	int					getDamage();
	int					getDefence();

	void				setHp(int value, int typeBranch);
	void				setDamage(int x, bool bAdd);


	//void				printStatus();
};

