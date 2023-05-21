#pragma once
#include "framework.h"
#include "Item.h"

class Merchant
{
private:
	std::string		name;
	std::vector<class Item*> itemList;

public:
	Merchant(std::string name);

	const std::string&	getName();
	class  Item*		getItem(int itemNum);
	int					getPrice(std::string itemName);
	int					getPrice(int itemNum);

	void				pushItem(class Item* item);
	void				pushItem(class Weapon* item);
	void				pushItem(class Armor* item);
	
	void				printItems();
	void				printText();
};