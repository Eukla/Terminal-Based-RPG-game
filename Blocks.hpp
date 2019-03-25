//FILE: �locks.hpp

#ifndef __LIVING_IN
	#define __LIVING_IN
	#include "Living.hpp"
#endif

#ifndef __DATA_STORING_IN
	#define __DATA_STORING_IN
	#include "DataStoring.hpp"
#endif	

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#ifndef __ITEMS_IN
	#define __ITEMS_IN
	#include "Items.hpp"
#endif

#ifndef __SPELLS_IN
	#define __SPELLS_IN
	#include "Spells.hpp"
#endif

class block
{
	blockCondition condition;
	
	protected:
	block(blockCondition currBlockCondition);
	
	public:
	blockCondition getBlockCond() const;
	virtual void buy(Hero *currHero,int heroNo) const{}
	virtual void sell(Hero *currHero,int heroNo) const{}
	virtual void showMenu() const{}
	virtual void engageInBattle(Hero *heroes[],int heroesNo) const{}
	virtual ~block(){}
};

class marketBlock:public block
{
	const database <class Weapon> 	 		&weaponsData;
	const database <class Armor> 	 		&armorsData;
	const database <class Potion> 	 		&potionsData;
	const database <class IceSpell>  	   	&iceSpellsData;
	const database <class FireSpell> 	    &fireSpellsData;
	const database <class LightningSpell>   &lightningSpellsData;
	
	public:
	marketBlock(const database <class Weapon>  &newWeaponsData, const database <class Armor> &newArmorsData, const database <class Potion> &newPotionsData,
	const database <class IceSpell> &newIceSpellsData, const database <class FireSpell> &newFireSpellsData,	const database <class LightningSpell> 
	&newLightningSpellsData);
	void buy(Hero *currHero,int heroNo) const;
	void sell(Hero *currHero,int heroNo) const;
	void showMenu() const;	
	
	private:
	void showWeaponsMenu(Hero *currHero=NULL,int heroNo=-1) const;	
	void showArmorsMenu(Hero *currHero=NULL,int heroNo=-1) const;
	void showPotionsMenu(Hero *currHero=NULL) const;
	void showIceSpellsMenu(Hero *currHero=NULL,int heroNo=-1) const;
	void showFireSpellsMenu(Hero *currHero=NULL,int heroNo=-1) const;
	void showLightningSpellsMenu(Hero *currHero=NULL,int heroNo=-1) const;						
};

class commonBlock:public block
{
	const double battleProb;
	const database <string> &characterData;
	
	public:
	commonBlock(const database <string> &newCharacterData);
	void engageInBattle(Hero *heroes[], int heroesNo) const;
	
	private:
	bool battle(Hero *heroes[],int HN,Monster *monsters[],int MN) const;
	void displayStats(Hero **heroes,int HN,Monster **monsters,int MN) const;
};

class nonAccessibleBlock: public block
{
	public:
	nonAccessibleBlock();
};
