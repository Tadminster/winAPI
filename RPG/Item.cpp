#include "Item.h"

Item::Item()
{
}

/* 아이템 */
Item::Item(std::string n, int p) : name(n), price(p) {}

Item::~Item()
{
	delete this;
}

int Item::getPrice()
{
	return this->price;
}

const std::string& Item::getName()
{
	return this->name;
}

Item Item::getItem()
{
	return *this;
}

Item* Item::getThis()
{
	return &(*this);
}

std::string Item::getType()
{
	return typeid(*this->createClone()).name();
}

void Item::setName(std::string name)
{
	this->name = name;
}

void Item::setPrice(int price)
{
	this->price = price;
}

void Item::setInfo(std::string texts)
{
	this->info = texts;
}

void Item::print()
{
	std::cout << "[";
	int space = (14 - this->name.size()) / 2;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << this->name;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << "]";

	std::cout << "\t가격: " << this->price;
	std::cout << "\t\t\t\t"  << this->info << std::endl;
}

Item* Item::createClone()
{
	return new Item(*this);
}

void Item::save(std::ofstream& outFile)
{
	outFile << this->name << " ";
	outFile << this->price << " ";
	//outFile << this->info << " ";
}

//void Item::load(std::ifstream& inFile)
//{
//	std::getline(inFile, this->name);
//	inFile >> this->price;
//	std::getline(inFile, this->info);
//}

/* 무기 */ 
Weapon::Weapon(std::string n, int p, int d) : Item(n, p), damage(d) {}

Weapon::Weapon(const Weapon& rhs) : Item(rhs), damage(rhs.damage) {}

Weapon::~Weapon()
{
	delete this;
}

int Weapon::getDMG()
{
	return this->damage;
}

void Weapon::setDMG(int damage)
{
	this->damage = damage;
}

void Weapon::print()
{
	std::cout << "[";
	int space = (14 - this->name.size()) / 2;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << this->name;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << "]";

	std::cout << "\t가격: " << this->price;
	std::cout << "\t공격력: " << this->damage;
	std::cout << "\t\t"  << this->info << std::endl;
}

Item* Weapon::createClone()
{
	return new Weapon(*this);
}

void Weapon::save(std::ofstream& outFile)
{
	Item::save(outFile);
	outFile << this->damage << " ";
}

//void Weapon::load(std::ifstream& inFile)
//{
//	Item::load(inFile);
//	inFile >> this->damage;
//}


/* 갑옷 */
Armor::Armor(std::string n, int p, int d, int v) : Item(n, p), defence(d), vision(v) {}
Armor::Armor(const Armor& rhs) : Item(rhs), defence(rhs.defence), vision(rhs.vision) {}

Armor::~Armor()
{
	delete this;
}

int Armor::getDEF()
{
	return this->defence;
}

int Armor::getVISION()
{
	return this->vision;
}

void Armor::setDEF(int defence)

{
	this->defence = defence;
}

void Armor::print()
{
	std::cout << "[";
	int space = (14 - this->name.size()) / 2;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << this->name;
	for (int i = 0; i < space; i++) std::cout << " ";
	std::cout << "]";

	std::cout << "\t가격: " << this->price;
	std::cout << "\t방어력: " << this->defence;
	std::cout << "\t\t" << this->info << std::endl;
}

Item* Armor::createClone()
{
	return new Armor(*this);
}

void Armor::save(std::ofstream& outFile)
{
	Item::save(outFile);
	outFile << this->defence << " ";
	outFile << this->vision << " ";
}

//void Armor::load(std::ifstream& inFile)
//{
//	Item::load(inFile);
//	inFile >> this->defence;
//	inFile >> this->vision;
//}
