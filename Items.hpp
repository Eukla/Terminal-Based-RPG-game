//FILE: Items.hpp
#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

using namespace std;
class Item
{
	const std::string name;
	const unsigned int price;
	const unsigned int level;
	const ItemSpell thing;


	protected:

	Item(std::string newName, unsigned int newPrice, unsigned int newLevel, ItemSpell newThing); 
	
	public:
	virtual ~Item(){}		//(needed cause there is no default virtual destructor)
	virtual unsigned int getDamage() const{}
	virtual unsigned int getHandsNeeded() const{}
	virtual unsigned int getDamageReduction() const{}
	virtual unsigned int getIncreament() const{}
	virtual statCategory getStat() const{}
	virtual void printInfo() const;
		string get_name() const;
	ItemSpell get_thing() const;
	unsigned int getPrice()const;
	unsigned int getLevel() const;
	static void printHeadline();																			
		
};

class Weapon: public Item
{
	const unsigned int damage;
	const unsigned int handsNeeded;

	public:
	Weapon(std::string newName, unsigned int newPrice, unsigned int newLevel,unsigned int newDamage,unsigned int newHandsNeeded);
	unsigned int getDamage() const;
	unsigned int getHandsNeeded() const;
	void printInfo() const;
	static void printHeadline();
};

class Armor: public Item
{
	const unsigned int damageReduction;

	public:
	Armor(std::string newName, unsigned int newPrice, unsigned int newLevel, unsigned int newDamageReduction);

	unsigned int getDamageReduction() const;
	void printInfo() const;
	static void printHeadline();
};

class Potion: public Item
{
	const statCategory stat;
	const unsigned int increament;

	public:
	Potion(std::string newName, unsigned int newPrice, unsigned int newLevel, unsigned int newIncreament, statCategory newStat);

	unsigned int getIncreament() const;
	statCategory getStat() const;
	void printInfo() const;
	static void printHeadline();
};
