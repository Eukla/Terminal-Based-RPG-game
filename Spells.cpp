//FILE: Spells.cpp
#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif

#ifndef __SPELLS_IN
	#define __SPELLS_IN
	#include "Spells.hpp"
#endif

#ifndef __LIVING_IN
	#define __LIVING_IN
	#include "Living.hpp"
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#define __MAX_DEXTERITY ((__MAXLEVEL)*(__DEXTERITY_SCALLING))

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Spell constructor
Spell::Spell(string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,unsigned int newMagicEnergyReq,
unsigned int newRoundsEffect, ItemSpell newThing): name(newName), price(newPrice), minLevel(newMinLevel), minDamage(newMinDamage), maxDamage(newMaxDamage), 
magicEnergyReq(newMagicEnergyReq), roundsEffect(newRoundsEffect), thing(newThing){}

ItemSpell Spell::get_thing() const
{
	return thing;
}

unsigned int Spell::getPrice() const
{
	return price;
}

unsigned int Spell::getMagicEnergyReq() const
{
	return magicEnergyReq;
}

unsigned int Spell::getRoundsEffect() const
{
	return roundsEffect;
}

void Spell::reduceRoundsEffect()
{
	roundsEffect--;
}

unsigned int Spell::getDamage(int dexterity) const
{
	return minDamage+(maxDamage-minDamage)*(double (dexterity-3))/(__MAX_DEXTERITY-3); 
}

void Spell::printInfo() const
{
	cout.width(20);cout<<left<<name;
	cout.width(10);cout<<left<<price;
	cout.width(10);cout<<left<<minLevel;
	cout.width(10);cout<<left<<minDamage;
	cout.width(10);cout<<left<<maxDamage;
	cout.width(15);cout<<left<<magicEnergyReq;
	cout.width(15);cout<<left<<roundsEffect;
}

unsigned int Spell::getLevel() const
{
	return minLevel;
}

void Spell::printHeadline()
{
	cout.width(20);cout<<left<<"Name";
	cout.width(10);cout<<left<<"Price";
	cout.width(10);cout<<left<<"minLevel";
	cout.width(10);cout<<left<<"minDamage";
	cout.width(10);cout<<left<<"maxDamage";
	cout.width(15);cout<<left<<"Magic Energy";
	cout.width(15);cout<<left<<"Rounds Effect";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//IceSpell constructor
IceSpell::IceSpell(string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
unsigned int newMagicEnergyReq, unsigned int newRoundsEffect, unsigned int newOppDamageDrop):
Spell(newName,newPrice,newMinLevel,newMinDamage,newMaxDamage,newMagicEnergyReq,newRoundsEffect,IceSpellS), oppDamageDrop(newOppDamageDrop){}

unsigned int IceSpell::getDrop() const
{
	return oppDamageDrop;
}

void IceSpell::printInfo() const
{
	Spell::printInfo();
	cout.width(15);cout<<left<<oppDamageDrop;
}

void IceSpell::printHeadline()
{
	Spell::printHeadline();
	cout.width(15);cout<<left<<"Damage Drop";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FireSpell constructor
FireSpell::FireSpell(string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
unsigned int newMagicEnergyReq,  unsigned int newRoundsEffect, unsigned int newOppDefenceDrop):
Spell(newName,newPrice,newMinLevel,newMinDamage,newMaxDamage,newMagicEnergyReq,newRoundsEffect,FireSpellS), oppDefenceDrop(newOppDefenceDrop){}

unsigned int FireSpell::getDrop() const
{
	return oppDefenceDrop;
}

void FireSpell::printInfo() const
{
	Spell::printInfo();
	cout.width(15);cout<<left<<oppDefenceDrop;
}

void FireSpell::printHeadline()
{
	Spell::printHeadline();
	cout.width(15);cout<<left<<"Defence Drop";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LightingSpell constructor
LightningSpell::LightningSpell(string newName, unsigned int newPrice, unsigned int newMinLevel, unsigned int newMinDamage, unsigned int newMaxDamage,
unsigned int newMagicEnergyReq,  unsigned int newRoundsEffect, unsigned int newOppAgilityDrop):
Spell(newName,newPrice,newMinLevel,newMinDamage,newMaxDamage,newMagicEnergyReq,newRoundsEffect,LightningSpellS), oppAgilityDrop(newOppAgilityDrop){}

unsigned int LightningSpell::getDrop() const
{
	return oppAgilityDrop;
}

void LightningSpell::printInfo() const
{
	Spell::printInfo();
	cout.width(15);cout<<left<<oppAgilityDrop;
}

void LightningSpell::printHeadline()
{
	Spell::printHeadline();
	cout.width(15);cout<<left<<"Agility Drop";
} 
