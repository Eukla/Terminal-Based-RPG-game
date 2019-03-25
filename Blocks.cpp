//FILE: Blocks.cpp

#ifndef __BLOCKS_IN
	#define __BLOCKS_IN
	#include "Blocks.hpp"
#endif	

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __LIVING_IN
	#define __LIVING_IN
	#include "Living.hpp"
#endif

#ifndef __CSTDLIB_IN
	#include <cstdlib>
	#define __CSTDLIB_IN
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#ifndef __ITEMS_IN
	#define __ITEMS_IN
	#include "Items.hpp"
#endif

#ifndef __CLIMITS_IN
	#define __CLIMITS_IN
	#include <climits>
#endif	

#ifndef __SPELLS_IN
	#define __SPELLS_IN
	#include "Spells.hpp"
#endif

#include "graphics.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//block constructor
block::block(blockCondition currBlockCondition):condition(currBlockCondition){}

blockCondition block::getBlockCond() const
{
	return condition;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//market block constructor
marketBlock::marketBlock(const database <class Weapon>  &newWeaponsData, const database <class Armor> &newArmorsData, const database <class Potion> &newPotionsData,
const database <class IceSpell> &newIceSpellsData, const database <class FireSpell> &newFireSpellsData,	const database <class LightningSpell> 
&newLightningSpellsData): block(market), weaponsData(newWeaponsData), armorsData(newArmorsData), potionsData(newPotionsData), iceSpellsData(newIceSpellsData),
fireSpellsData(newFireSpellsData), lightningSpellsData(newLightningSpellsData){}

void marketBlock::buy(Hero *currHero,int heroNo) const
{
	char choice;
	do
	{
		clearScreen();
		cout<<"Your bank account: "<<currHero->get_money()<<"$"<<endl;
		cout<<"What would you like to buy:"<<endl;
		cout<<"1.Weapon"<<endl;
		cout<<"2.Armor"<<endl;
		cout<<"3.Potion"<<endl;
		cout<<"4.Fire Spell"<<endl;
		cout<<"5.Ice Spell"<<endl;
		cout<<"6.Lightning Spell"<<endl;
		cout<<"7.back"<<endl;
		choice=unbufferedInput();
		
		bool illegal=0;
		do
		{
			int total;
			switch (choice)
			{
				case '1':
					total=weaponsData.size;
					showWeaponsMenu(currHero,heroNo);
					cout<<total+1<<".back"<<endl;
					break;
				case '2':
					total=armorsData.size;
					showArmorsMenu(currHero,heroNo);
					cout<<total+1<<".back"<<endl;
					break;
				case '3':
					total=potionsData.size;
					showPotionsMenu(currHero);
					cout<<total+1<<".back"<<endl;
					break;
				case '4':
					total=fireSpellsData.size;
					showFireSpellsMenu(currHero,heroNo);
					cout<<total+1<<".back"<<endl;
					break;
				case '5':
					total=iceSpellsData.size;
					showIceSpellsMenu(currHero,heroNo);
					cout<<total+1<<".back"<<endl;
					break;
				case '6':
					total=lightningSpellsData.size;
					showLightningSpellsMenu(currHero,heroNo);
					cout<<total+1<<": back"<<endl;
					break;
				case '7':
					break;	
				default:
					cout<<"\a";
				break;
			}
			if (choice>='1' && choice<='6')
			{
				int pick;
				cout<<"menu number: ";
				cin>>pick;
				if ((illegal=cin.fail())==0)
				{
					cin.ignore();
					if (illegal= (pick>total+1 || pick<1))
					{
						cout<<"\a";
					}
					else if (pick!=total+1)
					{
						unsigned int cost;
						unsigned int level;
						switch(choice)
						{
							case '1':
							{
								if (weaponsData.available[heroNo][pick-1]==0)
									cout<<"You have already bought this weapon"<<endl;
								else
								{	
									cost=weaponsData.obj[pick-1]->getPrice();
									level=weaponsData.obj[pick-1]->getLevel();
									if (cost<=currHero->get_money()  && level<=currHero->get_level())
									{
										currHero->Store(weaponsData.obj[pick-1],pick);
										currHero->set_money(currHero->get_money()-cost);
										weaponsData.available[heroNo][pick-1]=0;
										cout<<"The weapon was successfully purchased"<<endl;
									}
									else
									{
										if (level>currHero->get_level())
											cout<<"You haven't reached the minimum level required to buy this weapon"<<endl;
										else
											cout<<"You cannot afford this weapon"<<endl;
									}
									
								}
							break;
							}
							case '2':
							{
								if (armorsData.available[heroNo][pick-1]==0)
									cout<<"You have already bought this armor"<<endl;
								else
								{
									cost=armorsData.obj[pick-1]->getPrice();
									level=armorsData.obj[pick-1]->getLevel();
									if (cost<=currHero->get_money() && level<=currHero->get_level())
									{
										currHero->Store(armorsData.obj[pick-1],pick);
										currHero->set_money(currHero->get_money()-cost);
										armorsData.available[heroNo][pick-1]=0;
										cout<<"The armor was successfully purchased"<<endl;
									}
									else
									{
										if (level>currHero->get_level())
											cout<<"You haven't reached the minimum level required to buy this armor"<<endl;
										else
											cout<<"You cannot afford this amror"<<endl;
									}
								}
								break;
							}
							case '3':
							{
								cost=potionsData.obj[pick-1]->getPrice();
								level=potionsData.obj[pick-1]->getLevel();
								if (cost<=currHero->get_money() && level<=currHero->get_level())
								{
									currHero->Store(potionsData.obj[pick-1],pick);
									currHero->set_money(currHero->get_money()-cost);
									cout<<"The potion was successfully purchased"<<endl;
								}
								else
								{
									if (level>currHero->get_level())
										cout<<"You haven't reached the minimum level required to buy this potion"<<endl;
									else
										cout<<"You cannot afford this potion"<<endl;
								}
								break;
							}
							case '4':
							{
								if (fireSpellsData.available[heroNo][pick-1]==0)
									cout<<"You have already bought this fire spell"<<endl;
								else
								{
									cost=fireSpellsData.obj[pick-1]->getPrice();
									level=fireSpellsData.obj[pick-1]->getLevel();
									if (cost<=currHero->get_money() && level<=currHero->get_level())
									{
										currHero->Store(fireSpellsData.obj[pick-1],pick);
										currHero->set_money(currHero->get_money()-cost);
										fireSpellsData.available[heroNo][pick-1]=0;
										cout<<"The fire spell was successfully purchased"<<endl;
									}
									else
									{
										if (level>currHero->get_level())
											cout<<"You haven't reached the minimum level required to buy this fire spell"<<endl;
										else
											cout<<"You cannot afford this fire spell"<<endl;
									}
								}
								break;
							}
							case '5':
							{
								if (iceSpellsData.available[heroNo][pick-1]==0)
									cout<<"You have already bought this ice spell"<<endl;
								else
								{
									cost=iceSpellsData.obj[pick-1]->getPrice();
									level=iceSpellsData.obj[pick-1]->getLevel();
									if (cost<=currHero->get_money() && level<=currHero->get_level())
									{
										currHero->Store(iceSpellsData.obj[pick-1],pick);
										currHero->set_money(currHero->get_money()-cost);
										iceSpellsData.available[heroNo][pick-1]=0;
										cout<<"The ice spell was successfully purchased"<<endl;
									}
									else
									{
										if (level>currHero->get_level())
											cout<<"You haven't reached the minimum level required to buy this ice spell"<<endl;
										else
											cout<<"You cannot afford this ice spell"<<endl;
									}
								}
								break;
							}
							case '6':
							{
								if (lightningSpellsData.available[heroNo][pick-1]==0)
									cout<<"You have already bought this lightning spell"<<endl;
								else
								{
									cost=lightningSpellsData.obj[pick-1]->getPrice();
									level=lightningSpellsData.obj[pick-1]->getLevel();
									if (cost<=currHero->get_money() && level<=currHero->get_level())
									{
										currHero->Store(lightningSpellsData.obj[pick-1],pick);
										currHero->set_money(currHero->get_money()-cost);
										lightningSpellsData.available[heroNo][pick-1]=0;
										cout<<"The lightning spell was successfully purchased"<<endl;
									}
									else
									{
										if (level>currHero->get_level())
											cout<<"You haven't reached the minimum level required to buy this lightning spell"<<endl;
										else
											cout<<"You cannot afford this lightning spell"<<endl;
									}	
								}
								break;
							}
						}
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
				}
				else
				{
					cout<<"\a";
					cin.clear();
					cin.ignore(100,'\n');
				}
			}	
		}while (illegal);
	}while (choice!='7');
}

void marketBlock::sell(Hero *currHero,int heroNo) const
{
	char choice;
	do
	{
		clearScreen();
		cout<<"Your bank account: "<<currHero->get_money()<<"$"<<endl;
		cout<<"Check your inventory to sell:"<<endl;
		cout<<"1.Weapon"<<endl;
		cout<<"2.Armor"<<endl;
		cout<<"3.Potion"<<endl;
		cout<<"4.Fire Spell"<<endl;
		cout<<"5.Ice Spell"<<endl;
		cout<<"6.Lightning Spell"<<endl;
		cout<<"7.Exit"<<endl;
		int total;
		choice=unbufferedInput();
		bool illegal=0;
		int pick;
		do
		{
			clearScreen();
			switch (choice)
			{
				case '1':
					total=currHero->printList(currHero->get_List<class Weapon>());
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any weapons"<<endl;
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '2':
					total=currHero->printList(currHero->get_List<class Armor>());
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any armors"<<endl;
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '3':
					total=currHero->printList(currHero->get_List<class Potion>());
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any potions"<<endl;
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '4':
					total=currHero->printList(currHero->get_List<class FireSpell>());
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any fire spells"<<endl;
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '5':
					total=currHero->printList(currHero->get_List<class IceSpell>());
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any ice spells"<<endl;
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '6':
					total=currHero->printList(currHero->get_List<class LightningSpell>());	
					if (total==0)
					{
						cout<<currHero->get_name()<<" doesn't have any lightning spells"<<endl;	
						cout<<"Press any key to continue..."<<endl;
						unbufferedInput();
					}
					break;
				case '7':
					break;	
				default:
					cout<<"\a";
					break;
			}
			if (choice>='1' && choice<='6' && total!=0)
			{
				cout.width(2); cout.fill('0'); cout<<right<<total+1<<". Back"<<endl; cout.fill(' ');
				cout<<"number on list:";
				cin>>pick;
				if ((illegal=cin.fail())==0)
				{
					cin.ignore();
					if (illegal=(pick>total+1 || pick<1))
					{
						cout<<"\a";
					}
				}
				else
				{
					cout<<"\a";
					cin.clear();
					cin.ignore(100,'\n');
				}
			}
		}while (illegal);
		if (choice>='1' && choice<='6' && total!=0 && pick!=total+1)
		{
			int addMoney;
			int databasePos;
			switch(choice)
			{
				case '1':
					addMoney=currHero->Sell(pick, currHero->get_List <class Weapon> (),databasePos);
					currHero->withdrawWeapon(weaponsData.obj[databasePos-1]);
					weaponsData.available[heroNo][databasePos-1]=1;
					cout<<"The weapon was sold"<<endl;
					break;
				case '2':
					addMoney=currHero->Sell(pick, currHero->get_List <class Armor> (),databasePos);
					currHero->withdrawArmor(armorsData.obj[databasePos-1]);
					armorsData.available[heroNo][databasePos-1]=1;
					cout<<"The armor was sold"<<endl;
					break;
				case '3':
					addMoney=currHero->Sell(pick, currHero->get_List <class Potion> (),databasePos);
					cout<<"The potion was sold"<<endl;
					break;
				case '4':
					addMoney=currHero->Sell(pick, currHero->get_List <class FireSpell> (),databasePos);
					fireSpellsData.available[heroNo][databasePos-1]=1;
					cout<<"The fire spell was sold"<<endl;
					break;
				case '5':
					addMoney=currHero->Sell(pick, currHero->get_List <class IceSpell> (),databasePos);
					iceSpellsData.available[heroNo][databasePos-1]=1;
					cout<<"The ice spell was sold"<<endl;
					break;
				case '6':
					addMoney=currHero->Sell(pick, currHero->get_List<class LightningSpell>(),databasePos);
					lightningSpellsData.available[heroNo][databasePos-1]=1;
					cout<<"The lightning spell was sold"<<endl;
					break;	
			}
			currHero->set_money(currHero->get_money()+addMoney);
			cout<<"Press any key to continue..."<<endl;
			unbufferedInput();
		}
	}while (choice!='7');
}

void marketBlock::showMenu() const
{
	char choice;
	do
	{
		clearScreen();
		cout<<"1.Check Items"<<endl;
		cout<<"2.Check Spells"<<endl;
		cout<<"3.Back"<<endl;
		choice=unbufferedInput();
		switch (choice)
		{
			case '1':
			{
				char choice;
				do
				{
					clearScreen();
					cout<<"1.Weapons Menu"<<endl;
					cout<<"2.Armors Menu"<<endl;
					cout<<"3.Potions Menu"<<endl;
					cout<<"4.Back"<<endl;
					choice=unbufferedInput();
					switch (choice)
					{
						case '1':
						{
							showWeaponsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}
						case '2':
						{
							showArmorsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}
						case '3':
						{
							showPotionsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}
						case '4':
						{
							break;
						}
						default:
						{
							cout<<"\a";
						}
					}
				}while(choice!='4');
				break;
			}
			case '2':
			{
				char choice;
				do
				{
					clearScreen();
					cout<<"1.Ice Spell"<<endl;
					cout<<"2.Fire Spell"<<endl;
					cout<<"3.Lightning Spell"<<endl;
					cout<<"4.Back"<<endl;
					choice=unbufferedInput();
					switch (choice)
					{
						case '1':
						{
							showIceSpellsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}	
						case '2':
						{
							showFireSpellsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}
						case '3':
						{
							showLightningSpellsMenu();
							cout<<"Press any key to continue..."<<endl;
							unbufferedInput();
							break;
						}
						case '4':
						{
							break;
						}
						default:
						{
							cout<<"\a";
						}
					}	
				}while(choice!='4');
				break;
			}
			case '3':
			{
				break;
			}
			default:
			{
				cout<<"\a";
				break;
			}
		}
	}while(choice!='3');
}



void marketBlock::showWeaponsMenu(Hero *currHero,int heroNo) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	
	int temp=weaponsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}	
	
	cout.width(digits+1);cout<<"";
	Weapon::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	int i;
	for (i=0;i<weaponsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		weaponsData.obj[i]->printInfo();
		if (currHero!=NULL && weaponsData.available[heroNo][i]==0)
		{
			cout.width(20);cout<<left<<"(already bought)";
		}
		if (weaponsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (weaponsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

void marketBlock::showArmorsMenu(Hero *currHero,int heroNo) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	int temp=armorsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}
	
	cout.width(digits+1);cout<<"";
	Armor::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	
	
	int i;
	for (i=0;i<armorsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		armorsData.obj[i]->printInfo();
		if (currHero!=NULL && armorsData.available[heroNo][i]==0)
		{
			cout<<"(already bought)";
		}
		if (armorsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (armorsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

void marketBlock::showPotionsMenu(Hero *currHero) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	int temp=potionsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}
	
	cout.width(digits+1);cout<<"";
	Potion::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	
	int i;
	for (i=0;i<potionsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		potionsData.obj[i]->printInfo();
		if (currHero!=NULL && potionsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (potionsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

void marketBlock::showIceSpellsMenu(Hero *currHero,int heroNo) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	int temp=iceSpellsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}
	
	cout.width(digits+1);cout<<"";
	IceSpell::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	
	int i;
	for (i=0;i<iceSpellsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		iceSpellsData.obj[i]->printInfo();
		if (currHero!=NULL && iceSpellsData.available[heroNo][i]==0)
		{
			cout<<"(already bought)";
		}
		if (iceSpellsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (iceSpellsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

void marketBlock::showFireSpellsMenu(Hero *currHero,int heroNo) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	int temp=fireSpellsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}
	
	cout.width(digits+1);cout<<"";
	FireSpell::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	
	int i;
	for (i=0;i<fireSpellsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		fireSpellsData.obj[i]->printInfo();
		if (currHero!=NULL && fireSpellsData.available[heroNo][i]==0)
		{
			cout<<"(already bought)";
		}
		if (fireSpellsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (fireSpellsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

void marketBlock::showLightningSpellsMenu(Hero *currHero,int heroNo) const
{
	clearScreen();
	unsigned int level;
	unsigned int money;
	if (currHero==NULL)
	{
		level=__MAXLEVEL;
		money=UINT_MAX;
	}
	else
	{
		level=currHero->get_level();
		money=currHero->get_money();
	}
	
	int temp=lightningSpellsData.size;
	int digits=1;
	while((temp=temp/10)>0)
	{
		digits++;
	}
	
	cout.width(digits+1);cout<<"";
	LightningSpell::printHeadline();
	if (currHero!=NULL)
	{
		cout.width(15);cout<<left<<"Restrictions";
	}
	cout<<endl;
	int i;
	for (i=0;i<lightningSpellsData.size;i++)
	{
		cout.width(digits);cout.fill('0');cout<<right<<i+1;
		cout<<".";cout.fill(' ');
		lightningSpellsData.obj[i]->printInfo();
		if (currHero!=NULL && lightningSpellsData.available[heroNo][i]==0)
		{
			cout<<"(already bought)";
		}	
		if (lightningSpellsData.obj[i]->getLevel()>level)
		{
			cout.width(20);cout<<left<<"(smaller level)";
		}
		if (lightningSpellsData.obj[i]->getPrice()>money)
		{
			cout<<"(less money)";
		}
		cout<<endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

commonBlock::commonBlock(const database <string> &newCharacterData): block(common), characterData(newCharacterData), battleProb(0.2){}

void commonBlock::engageInBattle(Hero *heroes[],int heroesNo) const
{
	if (double (rand())/RAND_MAX<battleProb)
	{
		cout<<"\t \t ";
		print("BATTLE ENGAGED",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		Monster *battleMonsters[3];
		int monsterNo=1+rand()%3;
		int i,number;
		for (i=0;i<monsterNo;i++)
		{
			int random;
			do
			{
				random=rand()%characterData.size;

			}while (characterData.available[random]==0);
			int level=heroes[rand()%heroesNo]->get_level()-2+rand()%5;			
			if (level<1)			
				level=1;
			else if (level>10)
				level=10;
			number=rand()%3;
			if(number==0)
				battleMonsters[i]=new Exoskeleton(characterData.obj[random],level,100);
			else if(number==1)
				battleMonsters[i]=new Dragon(characterData.obj[random],level,100);
			else if(number==2)
				battleMonsters[i]=new Spirit(characterData.obj[random],level,100);
		}
		bool win=battle(heroes,heroesNo,battleMonsters,monsterNo);
		for (i=0;i<heroesNo;i++)
		{
			if (win==0)
			{
				heroes[i]->set_money(heroes[i]->get_money()/2);
				heroes[i]->set_HP(50);
				heroes[i]->set_life(1);
			}
			else
			{
				double monsterFactor=0.0;
				int j;
				for (j=0;j<monsterNo;j++)
				{
					monsterFactor+=battleMonsters[j]->get_level();
				}
				if (heroes[i]->Faint())
				{
					heroes[i]->set_HP(50);
					heroes[i]->set_life(1);
				}
				else
				{
					int money=(double (heroes[i]->get_level())/__MAXLEVEL)*monsterNo*250;
					heroes[i]->set_money((heroes[i]->get_money())+money);
					if (heroes[i]->get_level()<10)
					{
						int exp=monsterFactor/heroes[i]->get_level()*10;
						exp+=heroes[i]->get_exp();
						if (exp>=100)
						{
							heroes[i]->level_up();
							if (heroes[i]->get_level()==10)
								heroes[i]->set_exp(0);
							else
								heroes[i]->set_exp(exp-100);
						}
						else
						{
							heroes[i]->set_exp(exp);
						}
					}
				}
			}
		}
		for(i=0;i<monsterNo;i++){
			delete battleMonsters[i];
		}
	}
}
void commonBlock::displayStats(Hero **heroes,int HN,Monster **monsters,int MN) const
{
  int i;
      for(i=0;i<HN;i++){
        heroes[i]->displayStats();
      }
      for(i=0;i<MN;i++){
        monsters[i]->displayStats();
      }
}
bool commonBlock::battle(Hero *heroes[],int HN,Monster *monsters[],int MN) const
{
  int currH=HN;
  int currM=MN;
  int i,rounds,value,decrement,used=0;
  char choice;
  Spell *spell;
  while( currH && currM)
  {
	for(i=0;i<HN && currM>0 ;i++)
	{
    if(heroes[i]->Faint()==0)
    	do
      	{	used=0;
		clearScreen();
    	cout<<"What do you want "<<heroes[i]->get_name()<<" to do ? "<<endl;
		cout<<"1.Attack"<<endl<<"2.Use a spell"<<endl<<"3.Use a Potion"<<endl<<"4.Change Armor/Weapons"<<endl<<"5.Display stats"<<endl;
			choice=unbufferedInput();								
      		switch(choice)
	  		{
       			case('1'):
        		{	clearScreen();
					currM-=heroes[i]->attack(monsters,MN,used);
					cout<<"Press any key to continue..."<<endl;
					unbufferedInput();
					break;
				}
        		case('2'):
        		{
					clearScreen();
					currM-=heroes[i]->CastSpell(monsters,MN,used);
					cout<<"Press any key to continue..."<<endl;
					unbufferedInput();
				 	break;
				}
        		case('3'):
				{ 
					clearScreen();
					used=heroes[i]->use();
					break;
    			}
    		    case('4'):
				{
					clearScreen();
					used=heroes[i]->equip();
    	    		break;
    			}
				case('5'):
				{
					clearScreen();
					displayStats(heroes,HN,monsters,MN);	
					cout<<"Press any key to continue..."<<endl;
					unbufferedInput();		
					break;
				}
				default:
				{
					cout<<"\a";
					break;
				}
    		}
    	}while(choice<'1' || choice>='5'||!used);			//added >= so that display stats doesnt take a turn 
	}
	clearScreen();
    for(i=0;i<MN && currH>0; i++)
	{
      if(monsters[i]->Faint()==0)
        currH-=monsters[i]->attack(heroes,HN);
		
    }
	cout<<"Press any key to continue..."<<endl;
	unbufferedInput();
    for(i=0;i<MN; i++)
	{                                           //Spells effect
    	if(monsters[i]->Faint()==0)
		{	

    		spell = monsters[i]->get_affliction();

    		if(spell!=NULL && spell->getRoundsEffect())
			{
    			spell->reduceRoundsEffect();
        	}
			else if(spell!=NULL)
			{
				if (spell->getRoundsEffect()==0)
				{
        			monsters[i]->refresh();
      			}
			}
    	}
    }
	clearScreen();
  }
  if(currM==0)
      return 1;
  else if(currH==0)    //new condition to solve the errors
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

nonAccessibleBlock::nonAccessibleBlock(): block(nonAccessible){}
