#include "Monster.h"

Monster::Monster(std::string n, int hp, int dmg, int def, int gold) : name(n), maxHP(hp), healthPoint(hp), damage(dmg), defence(def), bounty(gold) {}

const std::string& Monster::getName()
{
	return this->name;
}

int Monster::getGold()
{
	return this->bounty;
}

int Monster::getMaxHp()
{
	return this->maxHP;
}

int Monster::getHp()
{
	return this->healthPoint;
}

int Monster::getDamage()
{
	return this->damage;
}

int Monster::getDefence()
{
	return this->defence;
}

void Monster::setHp(int value, int typeBranch)
{
	if (typeBranch == 0)
		this->healthPoint = value;
	else if (typeBranch == 1)
		this->healthPoint = std::min(this->healthPoint + value, this->maxHP);
	else if (typeBranch == 2)
		this->healthPoint = std::max(this->healthPoint - value, 0);
}

void Monster::setDamage(int x, bool bAdd)
{
	if (bAdd) this->damage += x;
	else this->damage -= x;
}
