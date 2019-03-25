//FILE: gamingSystem.hpp
#ifndef __BLOCKS_IN
	#define __BLOCKS_IN
	#include "Blocks.hpp"
#endif

#ifndef __LIVING_IN
	#define __LIVING_IN
	#include "Living.hpp"
#endif

#ifndef __DATA_STORING_IN
	#define __DATA_STORING_IN
	#include "dataStoring.hpp"
#endif	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

class Grid
{
	static const unsigned int length=20;
	static const unsigned int width=20;
	
	const double commonProb;
	const double marketProb;
	const double nonAccesibleProb;
	
	unsigned int currRow;
	unsigned int currColumn;

	block ***map;
	
	public:
	Grid(const database <string> &characterData, const database <class Weapon> &weaponsData,
	const database <class Armor> &armorsData, const database <class Potion> &potionsData, const database <class IceSpell> &iceSpellsData,
	const database <class FireSpell> &fireSpellsData, const database <class LightningSpell> &lightningSpellsData);
	~Grid();
	
	bool move(Hero *heroes[], int myHeroes, char move);
	void displayMap(Hero *main) const;
	block* getCurrBlock() const;
};


class Game
{	
	
	database <string> characterData;
	database <class Weapon> weaponsData;
	database <class Armor> armorsData;
	database <class Potion> potionsData;
	database <class IceSpell> iceSpellsData;
	database <class FireSpell> fireSpellsData;
	database <class LightningSpell> lightningSpellsData;
	
	int mainHero;
	int myHeroes;
	bool active;
	Grid gameGrid;
	Hero *heroes[3];

	public:
	Game(std::string *namesArray[], int namesNo[]);
	~Game();
	void displayInfo() const;
	bool isActive() const;
	void chooseAction();
	void quitGame();
	void changeMainHero();
	
	private:
	void addNewHero();
	void cancelHero();
};
