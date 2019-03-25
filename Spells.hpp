//FILE: Spells.hpp
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

class Spell
{
	private:
	const std::string name;
	const unsigned int price;
	const unsigned int minLevel;
	const unsigned int minDamage;
	const unsigned int maxDamage;
	const ItemSpell thing;
	
	protected:
	const unsigned int magicEnergyReq;
	unsigned int roundsEffect;	
	
	protected:	
	Spell(std::string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
	unsigned int newMagicEnergyReq, unsigned int newRoundsEffect, ItemSpell newThing);
	
	public:
	virtual ~Spell(){}					//(needed cause there is no default virtual destructor)
	ItemSpell get_thing() const;
	unsigned int getLevel() const;
	unsigned int getPrice() const;
	unsigned int getMagicEnergyReq() const;
	unsigned int getRoundsEffect() const;
	void reduceRoundsEffect();
	unsigned int getDamage(int dexterity) const;
	virtual void printInfo() const;
	virtual unsigned int getDrop() const=0;
	static void printHeadline(); 
	

};

class IceSpell: public Spell
{
	const unsigned int oppDamageDrop;
	
	public:
	IceSpell(std::string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
	unsigned int newMagicEnergyReq,  unsigned int newRoundsEffect, unsigned int newOppDamageDrop);
	
	unsigned int getDrop() const;
	void printInfo() const;
	static void printHeadline(); 
};

class FireSpell: public Spell
{
	const unsigned int oppDefenceDrop;
	
	public:
	FireSpell(std::string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
	unsigned int newMagicEnergyReq,  unsigned int newRoundsEffect, unsigned int newOppDefenceDrop);	
	
	unsigned int getDrop() const;
	void printInfo() const;
	static void printHeadline(); 
};

class LightningSpell: public Spell
{
	const unsigned int oppAgilityDrop;
	
	public:
	LightningSpell(std::string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
	unsigned int newMagicEnergyReq,  unsigned int newRoundsEffect, unsigned int newOppAgilityDrop);	
	
	unsigned int getDrop() const;
	void printInfo() const;
	static void printHeadline(); 
};
