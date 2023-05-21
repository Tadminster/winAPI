#include "BattleSystem.h"

BattleSystem::BattleSystem(RPG_Player* p) : player(p), monster(nullptr) {}

//BattleSystem::~BattleSystem()
//{
//	delete this->player;
//	delete this->monster;
//}

void BattleSystem::setEnemy(Monster* monster)
{
	this->monster = monster;
}

void BattleSystem::startBattle()
{
	while (this->player->getHp() > 0 && this->monster->getHp() > 0)
	{
		int playerDamage = std::max(this->player->getDamage() - this->monster->getDefence(), 0);
		int monsterDamage = std::max(this->monster->getDamage() - this->player->getDefence(), 0);

		this->monster->setHp(playerDamage, 2);
		this->player->setHp(monsterDamage, 2);

		std::cout << "플레이어: " << this->player->getHp() << "/" << this->player->getMaxHp() << std::endl;
		std::cout << "몬스터: " << this->monster->getHp() << "/" << this->monster->getMaxHp() << std::endl << std::endl;

		std::cout << "계속하려면 아무키나 입력하세요." << std::endl;
		_getch();
	}

	if (this->player->getHp() <= 0)
	{
		std::cout << "플레이어는 몬스터에게 무참히 살해당했다.." << std::endl;

		std::cout << "계속하려면 아무키나 입력하세요." << std::endl;
		_getch();
	}
	else
	{
		int bounty{ this->monster->getGold() };
		std::cout << "플레이어가 몬스터를 물리쳤습니다!" << std::endl;
		std::cout << "시체를 뒤져 " << bounty << "골드 획득!" << std::endl;
		player->setMoney(bounty, 1);
	}
}
