//FILE: Items.cpp

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <string>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif

#ifndef __ITEMS_IN
	#define __ITEMS_IN
	#include "Items.hpp"
#endif

#include "Enums.hpp"

using namespace std;

//item constructor
Item::Item(string newName, unsigned int newPrice, unsigned int newLevel, ItemSpell newThing):name(newName), price(newPrice), level(newLevel), thing(newThing){}

//accessor of price
unsigned int Item::getPrice() const
{
	return price;
}

//print item's info
void Item::printInfo() const
{
	cout.width(20);cout<<left<<name;
	cout.width(20);cout<<left<<price;
	cout.width(20);cout<<left<<level;
}

string Item::get_name()const{
		return name;
}
//accessor of thing
ItemSpell Item::get_thing() const
{
	return thing;
}

//accessor of level
unsigned int Item::getLevel() const
{
	return level;
}

void Item::printHeadline()
{
	cout.width(20);cout<<left<<"Name";
	cout.width(20);cout<<left<<"Price";
	cout.width(20);cout<<left<<"minLevel";
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//weapon constructor
Weapon::Weapon(string newName, unsigned int newPrice, unsigned int newLevel,unsigned int newDamage,unsigned int newHandsNeeded):
Item(newName,newPrice,newLevel,WeaponI),damage(newDamage), handsNeeded(newHandsNeeded){}

//accessor of damage
unsigned int Weapon::getDamage() const
{
	return damage;
}

//accessor of handsNeeded
unsigned int Weapon::getHandsNeeded() const
{
	return handsNeeded;
}

//prints weapon's info
void Weapon::printInfo() const
{
	Item::printInfo();
	cout.width(20);cout<<left<<damage;
	cout.width(20);cout<<left<<handsNeeded;
}

void Weapon::printHeadline()
{
	Item::printHeadline();
	cout.width(20);cout<<left<<"Damage";
	cout.width(20);cout<<left<<"Hands";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//armor constructor
Armor::Armor(string newName, unsigned int newPrice, unsigned int newLevel, unsigned int newDamageReduction):Item(newName,newPrice,newLevel,ArmorI), 
damageReduction(newDamageReduction){}

//accessor of damageReduction
unsigned int Armor::getDamageReduction() const
{
	return damageReduction;
}

//prints armor's info
void Armor::printInfo() const
{
	Item::printInfo();
	cout.width(20);cout<<left<<damageReduction;
}

void Armor::printHeadline()
{
	Item::printHeadline();
	cout.width(20);cout<<left<<"Damage Reduction";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//potion constructor
Potion::Potion(string newName, unsigned int newPrice, unsigned int newLevel, unsigned int newIncreament, statCategory newStat):
Item(newName,newPrice,newLevel,PotionI),increament(newIncreament), stat(newStat) {}

//accessor of increamentPercentage
unsigned int Potion::getIncreament() const
{
	return increament;
}

//accessor of stat
statCategory Potion::getStat() const
{
	return stat;
}

//prints potion's info 
void Potion::printInfo() const
{
	Item::printInfo();
	switch(stat)
	{
		case healthPowerStat:
		{
			cout.width(20);cout<<left<<"health power";
			break;
		}
		case strengthStat:
		{
			cout.width(20);cout<<left<<"strength";
			break;
		}
		case agilityStat:
		{
			cout.width(20);cout<<left<<"agility";
			break;
		}
		case dexterityStat:
		{
			cout.width(20);cout<<left<<"dexterity";
			break;
		}
		case magicPowerStat:
		{
			cout.width(20);cout<<left<<"magic power";
			break;
		}	
	}
	cout.width(20);cout<<left<<increament;
}

void Potion::printHeadline()
{
	Item::printHeadline();
	cout.width(20);cout<<left<<"Category";
	cout.width(20);cout<<left<<"Increament";
}

