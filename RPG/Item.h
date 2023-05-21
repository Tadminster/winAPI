#pragma once
#include "framework.h"
#include "SaveLoadSystem.h"

class Item
{
protected:
	std::string			name;
	std::string			info;
	int					price;

public:
	Item();
	/* 이름, 가격*/
	Item(std::string n, int p);
	Item(const Item& rhs) : name(rhs.name), info(rhs.info), price(rhs.price) {}
	~Item();


	int						getPrice();
	const std::string&		getName();
	Item					getItem();
	Item*					getThis();
	virtual std::string		getType();

	void					setName(std::string name);
	void					setPrice(int price);
	void					setInfo(std::string texts);

	virtual void			print();
	virtual Item*			createClone();

	virtual void			save(std::ofstream& outFile);
	//virtual void			load(std::ifstream& inFile);
};

class Weapon : public Item
{
protected:
	int					damage;
public:
	/* 이름, 가격, 공격력*/
	Weapon(std::string n, int p, int d);
	Weapon(const Weapon& rhs);
	~Weapon();

	int					getDMG();

	void				setDMG(int damage);
	void				print() override;
	Item*				createClone() override;

	void				save(std::ofstream& outFile) override;
	//void				load(std::ifstream& inFile) override;
};

class Armor : public Item
{
protected:
	int					defence;
	int					vision;
public:
	/* 이름, 가격, 방어력, 시야*/
	Armor(std::string n, int p, int d, int v);
	Armor(const Armor& rhs);
	~Armor();

	int					getDEF();
	int					getVISION();

	void				setDEF(int defence);

	void				print() override;
	Item*				createClone() override;

	void				save(std::ofstream& outFile) override;
	//void				load(std::ifstream& inFile) override;
};
