#include "Player.h"

RPG_Player::RPG_Player()
	: maxHP(100), healthPoint(100), maxSP(100), stamiaPoint(100),
	damage(10), defence(0), money(100), location{ 3, 3 }, visibleRadius(2) {}

RPG_Player::RPG_Player(int maxHP, int hp, int maxSP, int sp, int dmg, int def, int gold, int locationX, int locationY, int v)
	: maxHP(hp), healthPoint(hp), maxSP(sp), stamiaPoint(sp),
	damage(dmg), defence(def), money(gold), location{ locationX, locationY }, visibleRadius(v) {}

void RPG_Player::setHp(int value, int typeBranch)
{
	if (typeBranch == 0)
		this->healthPoint = value;
	else if (typeBranch == 1)
		this->healthPoint = std::min(this->healthPoint + value, this->maxHP);
	else if (typeBranch == 2)
		this->healthPoint = std::max(this->healthPoint - value, 0);
}

void RPG_Player::setSp(int value, int typeBranch)
{
	if (typeBranch == 0)
		this->stamiaPoint = value;
	else if (typeBranch == 1)
		this->stamiaPoint = std::min(this->stamiaPoint + value, this->maxSP);
	else if (typeBranch == 2)
		this->stamiaPoint = std::max(this->stamiaPoint - value, 0);
}

void RPG_Player::setDamage(int x, bool bAdd)
{
	if (bAdd)
		this->damage += x;
	else
		this->damage -= x;
}

void RPG_Player::setMoney(int value, int typeBranch)
{
	if (typeBranch == 0)
		this->money = value;
	else if (typeBranch == 1)
		this->money += value;
	else if (typeBranch == 2)
		this->money -= value;
}

void RPG_Player::setLocation(int y, int x)
{
	this->location[0] = y;
	this->location[1] = x;
}

void RPG_Player::setVisibleRadius(int x, bool bAdd)
{
	if (bAdd)
		this->visibleRadius += x;
	else
		this->visibleRadius -= x;
}

void RPG_Player::setItemStats(Item* item, bool bAdd)
{
	// 
}

void RPG_Player::setWeaponStats(Weapon* item, bool bAdd)
{
	RPG_Player::setItemStats(item->createClone(), bAdd);

	if (bAdd)
		this->damage += item->getDMG();
	else
		this->damage -= item->getDMG();
}

void RPG_Player::setArmorStats(Armor* item, bool bAdd)
{
	RPG_Player::setItemStats(item->createClone(), bAdd);

	if (bAdd)
	{
		this->defence += item->getDEF();
		this->visibleRadius += item->getVISION();
	}
	else
	{
		this->defence -= item->getDEF();
		this->visibleRadius -= item->getVISION();
	}
}


std::string RPG_Player::movePlayer(MazeMap* map, int arrow)
{
	// 이동할 위치 설정
	int target[2] = { this->getLocation(0), this->getLocation(1) };
	if (arrow == 1)			target[0]--;	// UP
	else if (arrow == 2)	target[0]++;	// DOWN
	else if (arrow == 3)	target[1]--;	// LEFT
	else if (arrow == 4)	target[1]++;	// RIGHT
	
	std::cout << std::endl;
	if (map->getMap(target[0], target[1]) == ".")
	{
		// 막힌 곳
		std::cout << "벽으로 막혀있습니다." << std::endl;
		return map->getMap(target[0], target[1]);
	}
	else
	{
		// 방의 정보를 저장할 임시 string
		std::string room{ map->getMap(target[0], target[1]) };

		// 지나온 길 표시
		if (map->getMap(target[0], target[1]) != "X")
			map->getMap(target[0], target[1]) = "X";

		// 갈 수 있는 곳이면 스왑, 좌표 재설정
		map->swapMap(this->getLocation(0), this->getLocation(1), target[0], target[1]);
		this->setLocation(target[0], target[1]);

		return room;
	}
}

const std::string& RPG_Player::getName()
{
	return this->name;
}

int RPG_Player::getMoney()
{
	return this->money;
}

int RPG_Player::getPrice(int index)
{
	int temp{ 1 };
	for (const auto& item : this->inventory)
	{
		if (index == temp)
		{
			return item.first->getPrice();
		}
		temp++;
	}
	return 0;
}

int RPG_Player::getItemQuantity(int index)
{
	int temp{ 1 };
	for (const auto& item : this->inventory)
	{
		if (index == temp)
		{
			return item.second;
		}
		temp++;
	}
	return 0;
}

int RPG_Player::getLocation(int location)
{
	if (location == 0) return this->location[0];
	else if (location == 1) return this->location[1];
	return 0;
}

int RPG_Player::getVisibleRadius()
{
	return this->visibleRadius;
}

Item* RPG_Player::getItem(int itemListNum)
{
	int temp{ 1 };
	for (const auto& item : this->inventory)
	{
		if (temp == itemListNum)
			return item.first;
		temp++;
	}
	return 0;
}

int RPG_Player::getHp()
{
	return this->healthPoint;
}

int RPG_Player::getMaxHp()
{
	return this->maxHP;
}

int RPG_Player::getSp()
{
	return this->stamiaPoint;
}

int RPG_Player::getMaxSp()
{
	return this->maxSP;
}

int RPG_Player::getDamage()
{
	return this->damage;
}

int RPG_Player::getDefence()
{
	return this->defence;
}

void RPG_Player::printStatus()
{
	std::cout << std::endl
		<< "플레이어 상태창" << std::endl
		<< "HP: " << this->healthPoint << "/" << this->maxHP << "\t"
		<< "SP: " << this->stamiaPoint << "/" << this->maxSP << "\t"
		<< "시야: " << this->visibleRadius << "칸" << std::endl
		<< "공격력: " << this->damage << "\t"
		<< "방어력: " << this->defence << std::endl;
	std::cout << std::endl << std::endl;
}

void RPG_Player::printInventory()
{
	std::cout << "인벤토리: ";
	
	// 돈이 1골드 이상 있으면 출력
	if (this->money > 0) std::cout << "골드(" << this->money << ") ";

	// 평소엔 아이템 이름만 출력
	for (const auto& item : this->inventory)
	{
		std::cout << item.first->getName();
		if (item.second > 1) std::cout << "(" << item.second << ")";
		std::cout << " ";
	}
	std::cout << std::endl;
}

void RPG_Player::printInventory_whenSelling()
{
	int maximumItemName{ 12 };	// 아이템은 최대 한글 6자
	int maximumItemNum{ 4 };	// 아이템 최대 소지량은 9999개
	int temp{ 1 };
	for (const auto& item : this->inventory)
	{
		int price = static_cast<int>(item.first->getPrice() * 0.75);
		std::cout << "[" << temp++ << "] ";		// index
		
		std::cout << item.first->getName() << " ";		// 아이템 이름
		for (int i = 0; i < maximumItemName - item.first->getName().size(); i++)
			std::cout << " ";

		std::cout << "\t수량: " << item.second;	// 아이템 수량
		for (int i = 0; i < maximumItemNum - std::to_string(item.second).size(); i++)
				std::cout << " ";

		std::cout << "\t판매가: " << price << std::endl; // 판매가
	}
	std::cout << std::endl;
}

void RPG_Player::saveInventory(std::ofstream& outFile)
{
	outFile << "INVENTORY_SIZE " << inventory.size() << std::endl;

	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		outFile << it->second << " " << it->first->getType() << " ";
		it->first->save(outFile);
	}
}

void RPG_Player::loadInventoty(std::ifstream& inFile)
{
	// Load inventory data
	std::string tempStr;
	int inventorySize;
	inFile >> tempStr >> inventorySize;
	for (int i = 0; i < inventorySize; i++)
	{

		int itemQuantity, itemCost, itemDMG, itemDEF, itemVISI;
		std::string itemType, itemName;
		// 로드될 데이터 순서
		// 수량 > class > 타입 > 이름 > 가격
		inFile >> itemQuantity >> tempStr >> itemType >> itemName >> itemCost;

			// Create new item object based on type
			Item* newItem = new Item();

		if (itemType == "Weapon")
		{
			inFile >> itemDMG;
			RPG_Player::addItem(new Weapon(itemName, itemCost, itemDMG), itemQuantity);
		}
		else if (itemType == "Armor")
		{
			inFile >> itemDEF >> itemVISI;
			RPG_Player::addItem(new Armor(itemName, itemCost, itemDEF, itemVISI), itemQuantity);
		}
		else
			RPG_Player::addItem(new Item(itemName, itemCost), itemQuantity);

	}
}

void RPG_Player::addItem(class Item* item, int quantity)
{
	// 인벤토리에 이미 가지고 있는 아이템인지 검사
	for (const auto& inven : this->inventory)
	{
		if (item->getName() == inven.first->getName())
		{
			// 있으면 개수 추가
			this->inventory[inven.first->getThis()] += quantity;
			return;
		}
	}

	// 없으면 새 아이템 추가
	this->inventory[item->createClone()] += quantity;

	Weapon* weaponPtr = dynamic_cast<Weapon*>(item);
	if (weaponPtr)
		RPG_Player::setWeaponStats(weaponPtr, true);
	else
	{
		Armor* armorPtr = dynamic_cast<Armor*>(item);
		if (armorPtr)
			RPG_Player::setArmorStats(armorPtr, true);
		else
			RPG_Player::setItemStats(item->createClone(), true);
	}
}

bool RPG_Player::removeItem(class Item* item, int quantity)
{
	int temp{ 1 };
	for (const auto& inven : this->inventory)
	{
		// 사용자입력 index와 실제 아이템 번호가 같으면
		/*if (index == temp)*/
		{
			// 객체의 수량 >= 삭제될 개수 
			if (this->inventory[item] >= quantity)
				this->inventory[item] -= quantity;
			else
			{
				std::cout << "아이템 개수를 확인하세요." << std::endl;
				break;
			}

			// 수량이 0이면, 삭제
			if (this->inventory[item] == 0)
			{
				this->inventory.erase(item);

				// 적용된 아이템옵션 제거
				Weapon* weaponPtr = dynamic_cast<Weapon*>(item);
				if (weaponPtr)
					RPG_Player::setWeaponStats(weaponPtr, false);
				else
				{
					Armor* armorPtr = dynamic_cast<Armor*>(item);
					if (armorPtr)
						RPG_Player::setArmorStats(armorPtr, false);
					else
						RPG_Player::setItemStats(item->createClone(), false);
				}

				// 객체 메모리 해제
				delete item;
			}

			return true;
		}
	}
	return false;
}
