#include "Inventory.h"

void Inventory::addItem(const class Item& item, int quantity)
{
	this->items[item] += quantity;
}

void Inventory::removeItem(const class Item& item, int quantity)
{
    if (this->items[item] >= quantity) {
        this->items[item] -= quantity;
    }
    else {
        throw std::runtime_error("Not enough items in the inventory");
    }
}
