//FILE: dataStoring.cpp
#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif


#ifndef __DATA_STORING_IN
	#define __DATA_STORING_IN
	#include "DataStoring.hpp"
#endif	


#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#include "Living.hpp"
#include <cstdlib>

#ifndef __SPELLS_IN
	#define __SPELLS_IN
	#include "Spells.hpp"
#endif

#ifndef __ITEMS_IN
	#define __ITEMS_IN
	#include "Items.hpp"
#endif

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
database<class Weapon>::database(std::string * const names, const int newSize): obj(new Weapon*[newSize]), size(newSize)
{
	int i;
	for (i=0;i<3;i++)
	{
		available[i]=new bool[size];
		int j;
		for (j=0;j<size;j++)
		{
			available[i][j]=1;
		}
	}
	unsigned int levelCounter=10;
	for (i=0;i<size;i++)
	{
		unsigned int minLevel=levelCounter;
		if (--levelCounter<1)
			levelCounter=10;
			
		unsigned int handsNeeded=1+(rand()%3==2);	
		unsigned int price=80+double (minLevel-1)/(__MAXLEVEL-1)*2220+rand()%201;
		unsigned int damage=20+(price-80)/2420.0*50.0*(2.0+handsNeeded)/4;
		obj[i]=new Weapon(names[i],price,minLevel,damage,handsNeeded);
	}
}

template<>
database<class Armor>::database(std::string * const names, const int newSize): obj(new Armor*[newSize]), size(newSize)
{
	int i;
	for (i=0;i<3;i++)
	{
		available[i]=new bool[size];
		int j;
		for (j=0;j<size;j++)
		{
			available[i][j]=1;
		}
	}
	unsigned int levelCounter=10;
	for (i=0;i<size;i++)
	{
		unsigned int minLevel=levelCounter;
		if (--levelCounter<1)
			levelCounter=10;
		
		unsigned int price=80+double (minLevel-1)/(__MAXLEVEL-1)*2220+rand()%201;
		unsigned int damageReduction=5+(price-80)/2420.0*35.0;			
					
		obj[i]=new Armor(names[i],price,minLevel,damageReduction);
	}
}

template<>
database <class Potion>::database(std::string * const names, const int newSize): obj(new Potion*[newSize]), size(newSize)
{
	int i;
	for (i=0;i<3;i++)
	{
		available[i]=new bool[size];
		int j;
		for (j=0;j<size;j++)
		{
			available[i][j]=1;
		}
	}
	unsigned int levelCounter=10;
	int statCounter=0;
	for (i=0;i<size;i++)
	{
		unsigned int minLevel=levelCounter;
		statCategory stat=statCategory (statCounter);
		if (++statCounter>4)
		{
			statCounter=0;
			if (--levelCounter<1)
				levelCounter=10;
		}
		
		unsigned int price=40+double (minLevel-1)/(__MAXLEVEL-1)*1060+rand()%101;
		unsigned int increament;
		if (stat==strengthStat|| stat==agilityStat || stat==dexterityStat)
			increament=3+(price-40)/1160.0*17;
		else
			increament=10+(price-40)/1160.0*30;
		obj[i]=new Potion(names[i],price,minLevel,increament,stat);
	}
}
	

template <class T>
database<T>::database(std::string * const names, const int newSize): obj(new T*[newSize]), size(newSize)
{
	int i;
	for (i=0;i<3;i++)
	{
		available[i]=new bool[size];
		int j;
		for (j=0;j<size;j++)
		{
			available[i][j]=1;
		}
	}
	unsigned int levelCounter=10;
	for (i=0;i<size;i++)
	{
		unsigned int minLevel=levelCounter;
		if (--levelCounter<1)
			levelCounter=10;
		
		unsigned int price=100+double (minLevel-1)/(__MAXLEVEL-1)*2200+rand()%201;
		unsigned int minDamage=40+(price-100)/2400.0*20;
		unsigned int maxDamage=minDamage+20;
		unsigned int magicEnergyReq=30;
		unsigned int roundsEffect=2;
		unsigned int drop=3*minLevel;
		obj[i]=new T(names[i],price,minLevel,minDamage,maxDamage,magicEnergyReq,roundsEffect,drop);
	}
}

template <class T>
database<T>::~database()
{
	int i;
	for (i=0;i<size;i++)
	{
		delete obj[i];
		obj[i]=NULL;
	}
	delete[] obj;
	for (i=0;i<3;i++)
		delete[] available[i];
}

template class database<class Weapon>;
template class database<class Armor>;
template class database<class Potion>;
template class database<class FireSpell>;
template class database<class IceSpell>;
template class database<class LightningSpell>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

database<string>::database(string * const names, const int newSize): obj(names), size(newSize), available(new bool[newSize])
{
	int i;
	for (i=0;i<size;i++)
	{
		available[i]=1;
	}
}

database<string>::~database()
{
	delete[] available;
}





