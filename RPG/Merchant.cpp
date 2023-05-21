#include "Merchant.h"

Merchant::Merchant(std::string name)
{
	this->name = name;
}

const std::string& Merchant::getName()
{
	return this->name;
}

class Item* Merchant::getItem(int itemNum)
{
	itemNum -= 1;
	return itemList[itemNum]->createClone();
}

int Merchant::getPrice(std::string itemName)
{
	for (auto& item : itemList)
	{
		if (itemName == item->getName())
			return item->getPrice();
	}
	return 0;
}

int Merchant::getPrice(int itemNum)
{
	itemNum -= 1;
	return itemList[itemNum]->getPrice();
}

void Merchant::pushItem(class Item* item)
{
	this->itemList.emplace_back(item->createClone());
}

void Merchant::pushItem(class Weapon* item)
{
	this->itemList.emplace_back(item->createClone());
}

void Merchant::pushItem(class Armor* item)
{
	this->itemList.emplace_back(item->createClone());
}

void Merchant::printItems()
{
	int tempNum{ 1 };

	Merchant::printText();
	std::cout << std::endl;
	std::cout << "[ESC] 상점 나가기" << std::endl;

	for (auto& item : itemList)
	{
		std::cout << "[" << tempNum++ << "]";
		item->print();
	}
	std::cout << std::endl;
}

void Merchant::printText()
{
	std::string npcText[] =
	{
		"천천히 둘러보시게",
		"좋은 물건이 많이 있다네",
		"오늘은 특별히 저렴한 가격에 내놓았네",
		"명품 좀 볼 줄 아나?",
		"이 칼이나 갑옷은 어떤가? 좋은 물건이라네",
		"이 물건은 어떤가? 자네에게 필요해 보이는군",
		"궁금한게 있다면 뭐든 물어보게나",
	};
	int arrSize = sizeof(npcText) / sizeof(std::string);
	int random = rand() % arrSize;

	std::cout << "상인의 말: " << npcText[random] << std::endl;
}
