#pragma once
#include "framework.h"
#include "Item.h"
#include "MazeMap.h"

class RPG_Player
{
private:
	int                     maxHP;
	int                     healthPoint;
	int                     maxSP;
	int                     stamiaPoint;
	int                     damage;
	int                     defence;
	int                     money;
	int						location[2];
	int						visibleRadius;

	std::string					name;
	std::map<class Item*, int>	inventory;

public:
	RPG_Player();
	RPG_Player(int maxHP, int hp, int maxSP, int sp, int dmg, 
		int def, int gold, int locationX, int locationY, int v);

	// 플레이어의 행동
	/* 플레이어 이동 (맵, 이동할 방향) */
	std::string				movePlayer(MazeMap* map, int arrow);

	// GET
	const std::string&	getName();
	int					getMoney();
	int					getPrice(int index);
	int					getItemQuantity(int index);
	int					getLocation(int location);
	int					getVisibleRadius();
	Item*				getItem(int itemListNum);

	int					getHp();						//전투관련
	int					getMaxHp();
	int					getSp();
	int					getMaxSp();
	int					getDamage();
	int					getDefence();

	// SET
	/* HP 설정 (설정값, {0=절대값, 1=더하기, 2=빼기} */
	void				setHp(int value, int typeBranch);
	/* SP 설정 (설정값, {0=절대값, 1=더하기, 2=빼기} */
	void				setSp(int value, int typeBranch);
	void				setDamage(int x, bool bAdd);
	/* 골드 설정 (설정값, {0=절대값, 1=더하기, 2=빼기} */
	void				setMoney(int value, int typeBranch);
	void				setLocation(int y, int x);
	void				setVisibleRadius(int x, bool bAdd);
	void				setItemStats(class Item* item, bool bAdd);
	void				setWeaponStats(class Weapon* item, bool bAdd);
	void				setArmorStats(class Armor* item, bool bAdd);

	void				printStatus();
	void				printInventory();
	void				printInventory_whenSelling();

	void				saveInventory(std::ofstream& outFile);
	void				loadInventoty(std::ifstream& inFile);
	void				addItem(Item* Item, int quantity);
	bool				removeItem(Item* item, int quantity);
};