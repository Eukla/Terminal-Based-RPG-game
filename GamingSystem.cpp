//FILE: gamingSystem.cpp
#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __GAMING_SYS_IN
	#define __GAMING_SYS_IN
	#include "GamingSystem.hpp"
#endif

#ifndef __CSTDLIB_IN
	#include <cstdlib>
	#define __CSTDLIB_IN
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#include "graphics.hpp"

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Game constructor
Game::Game(std::string *namesArray[], int namesNo[]):active(1), myHeroes(0), mainHero(0), characterData(namesArray[0],namesNo[0]) , weaponsData(namesArray[1],
namesNo[1]), armorsData(namesArray[2],namesNo[2]), potionsData(namesArray[3], namesNo[3]), fireSpellsData(namesArray[4],namesNo[4]),
iceSpellsData(namesArray[5],namesNo[5]), lightningSpellsData(namesArray[6],namesNo[6]),
gameGrid(characterData,weaponsData,armorsData,potionsData,iceSpellsData,fireSpellsData,lightningSpellsData)
{
	clearScreen();
	//opening lines
	print("Dragons's wings, they did darken the sky,\nThey roar fury's fire, and their scales sharpened scythes.\nMen ran and they cowered, and they fought and they died.\nThey burned and they bled as they issued their cries.\n",YELLOW,ITALIC);
	unbufferedInput();
	print("We need saviors to free us from the monsters's rage,\nHeroes who are strong , to lay them to waste",LIGHT_RED,ITALIC);
	unbufferedInput();
	clearScreen();
	bool begin=0;
	do
	{
		if (myHeroes==0)
			addNewHero();
		else
		{
			if (myHeroes<3)
			{
				bool fail;
				int choice;
				do
				{
					clearScreen();
					cout<<"My heroes"<<endl;
					int i;
					for (i=0;i<myHeroes;i++)
					{
						cout<<"Hero "<<i+1;
						heroes[i]->displayStats();
						cout<<endl;
					}
					cout<<endl;
					cout<<"1.New Hero"<<endl;
					cout<<"2.Delete Hero"<<endl;
					cout<<"3.Begin"<<endl;
					cout<<"Choice:";
					cin>>choice;
					if ((fail=cin.fail())==0)
					{
						cin.ignore();
						switch(choice)
						{
							case 1:
							{
								addNewHero();
								break;
							}
							case 2:
							{
								cancelHero();
								break;
							}
							case 3:
							{
								begin=1;
								break;
							}
							default:
							{
								cout<<"\a";
							}
						}
					}
					else
					{
						cout<<"\a";
						cin.clear();
						cin.ignore(100,'\n');
					}
				}while(fail==1 || choice<1 || choice>3);
			}
			else
			{
				int choice;
				bool fail;
				do
				{
					clearScreen();
					cout<<"My heroes"<<endl;
					int i;
					for (i=0;i<myHeroes;i++)
					{
						cout<<"Hero "<<i+1;
						heroes[i]->displayStats();
						cout<<endl;
					}
					cout<<endl;
					cout<<"1.Delete Hero"<<endl;
					cout<<"2.Begin"<<endl;
					cout<<"Choice:";
					cin>>choice;
					if ((fail=cin.fail())==0)
					{
						cin.ignore();
						switch(choice)
						{
							case 1:
							{
								cancelHero();
								break;
							}
							case 2:
							{
								begin=1;
								break;
							}
							default:
							{
								cout<<"\a";
							}
						}
					}
					else
					{
						cout<<"\a";
						cin.clear();
						cin.ignore(100,'\n');
					}
				}while(fail==1 || choice<1 || choice>2);
			}
		}
	}while (begin!=1);
}



//Game destructor
Game::~Game()
{
	int i;
	for (i=0;i<3;i++)
	{
		if (heroes[i]!=NULL)
		{
			delete heroes[i];
		}
	}
}

void Game::addNewHero()
{
	bool illegal;
	int heroChoice;
	do
	{
		clearScreen();
		cout<<"New hero"<<endl;
		int i;
		for (i=0;i<characterData.size;i++)
		{
			cout<<i+1<<"."<<characterData.obj[i];
			if (characterData.available[i]==0)
				cout<<" (already chosen)";
			cout<<endl;
		}
		cout<<"Your Hero:";
		cin>>heroChoice;
		if ((illegal=cin.fail())==0)
		{
			cin.ignore();
			if (illegal = (heroChoice<1 || heroChoice>characterData.size || characterData.available[heroChoice-1]==0))
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
	}while (illegal);
	characterData.available[heroChoice-1]=0;
	int fightingChoice;
	do
	{
		clearScreen();
		cout<<"Fighting Style of "<<characterData.obj[heroChoice-1]<<endl;
		cout<<"1.Warrior"<<endl;
		cout<<"2.Sorcerer"<<endl;
		cout<<"3.Palladin"<<endl;
		cout<<characterData.obj[heroChoice-1]<<"'s fighting style:";
		cin>>fightingChoice;
		if ((illegal=cin.fail())==0)
		{
			cin.ignore();
			if ((illegal=(fightingChoice<1 || fightingChoice>3))== 1)
			{
				cout<<"\a";
			}
			else
			{
				switch (fightingChoice)
				{
					case 1:
					{
						heroes[myHeroes]=new Warrior(characterData.obj[heroChoice-1],1,100,100,250);
						break;
					}
					case 2:
					{
						heroes[myHeroes]=new Sorcerer(characterData.obj[heroChoice-1],1,100,100,250);
						break;
					}
					case 3:
					{
						heroes[myHeroes]=new Paladin(characterData.obj[heroChoice-1],1,100,100,250);
						break;
					}
				}
				myHeroes++;
			}
		}
		else
		{
			cout<<"\a";
			cin.clear();
			cin.ignore(100,'\n');
		}
	}while (illegal);
}

void Game::cancelHero()
{
	int choice;
	bool illegal;
	do
	{
		clearScreen();
		if (myHeroes>0)
		{
			cout<<"My heroes"<<endl;
			int i;
			for (i=0;i<myHeroes;i++)
			{
				cout<<"Hero "<<i+1;
				heroes[i]->displayStats();
				cout<<endl;
			}
			cout<<endl;
		}
		cout<<"Hero to be cancelled:";
		cin>>choice;
		if ((illegal=cin.fail())==0)
		{
			cin.ignore();
			if ((illegal=(choice<1 || choice>myHeroes))==1)
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
	}while (illegal);
	int i;
	bool found=0;
	for (i=0;i<characterData.size && found==0 ;i++)
	{
		if (characterData.obj[i]==heroes[choice-1]->get_name())
		{
			characterData.available[i]=1;
			found=1;
		}
	}
	delete heroes[choice-1];
	for (i=choice-1;i<myHeroes-1;i++)
	{
		heroes[i]=heroes[i+1];
	}
	heroes[i]=NULL;
	myHeroes--;
}

void Game::displayInfo() const
{
	char choice;
	do
	{
		clearScreen();
		print("Info",YELLOW,BOLD,RED);
		cout<<endl;
		int i;
		for (i=1;i<=myHeroes;i++)
		{
			cout<<i<<"."<<heroes[i-1]->get_name()<<"'s info"<<endl;
		}
		cout<<i<<".Exit"<<endl;
		choice=unbufferedInput();
		if (choice<1+'0' || choice>myHeroes+1+'0')
			cout<<"\a";
		else if (choice!=myHeroes+1+'0')
		{
			clearScreen();
			heroes[choice-1-'0']->displayStats();
			cout<<"Press any key to continue..."<<endl;
  			unbufferedInput();
		}
	}while (choice!=myHeroes+1+'0');
}

bool Game::isActive() const
{
	return active;
}

void Game::quitGame()
{
	active=0;
}

void Game::changeMainHero()
{
	mainHero=(mainHero+1)%myHeroes;
}

void Game::chooseAction()
{
	static bool help=true;
	static int movesNo=0;
	clearScreen();
	gameGrid.displayMap(heroes[mainHero]);
	cout<<endl;
	if (help==true)
	{
		print("Map Guide",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		cout<<"*: nonAccessible Block"<<endl;
		cout<<"M: market Block"<<endl;
		cout<<"unmarked: common Block"<<endl;
		cout<<"Current position is marked with a bold capital letter, that is the first letter of the main hero's name."<<endl;

		print("Moving System",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		cout<<"W/w: move to the village forward"<<endl;
		cout<<"S/s: move to the village backward"<<endl;
		cout<<"A/a: move to the village left"<<endl;
		cout<<"D/d: move to the village right"<<endl;

		print("Heroes Control",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		cout<<"I:Display Heroes Info(name,level,health power,money,weapons in use,armors in use,magic power,experience,strength,agility and dexterity)"<<endl;
		if (myHeroes>1)
		{
			cout<<"C:Change main Hero (the hero after the one who is currently the main hero becomes the main hero. If the current main hero is the last one, the first hero becomes main one)";
		}
		cout<<endl;

		print("Armors/Weapons/Potions/Spells of main Hero",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		cout<<"B:Check "<<heroes[mainHero]->get_name()<<"'s "<<"bag"<<endl;
		cout<<"E:Equip "<<heroes[mainHero]->get_name()<<" with weapon/armor"<<endl;;
		cout<<"P:Use Potion to improve "<<heroes[mainHero]->get_name()<<"'s "<<"abilities"<<endl;
		if (gameGrid.getCurrBlock()->getBlockCond()==market)
		{
			print("You reached a shop , press M to enter \n",YELLOW,ITALIC);
		}
		print("K:show/hide keys",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		print("Q:Quit Game",RED,ITALIC,LIGHT_GREEN);
		cout<<endl;
		if (movesNo==3 && help==true){
				print("Dont forget you can always remove the instructions by pressing K",GREEN,ITALIC);
		}
	}
	else
	{
		print("Main hero:",LIGHT_RED,ITALIC);
		print(heroes[mainHero]->get_name(),LIGHT_RED,ITALIC);
		cout<<endl;
		print("K:show/hide keys",YELLOW,ITALIC);
		cout<<endl;
		if (gameGrid.getCurrBlock()->getBlockCond()==market)
		{
			print("You reached a shop , press M to enter",GREEN,ITALIC);
			cout<<endl;
		}
	}

	char answer=unbufferedInput();
	if (answer=='W' || answer=='A' || answer=='S' || answer=='D' || answer=='w' || answer=='a' || answer=='s' || answer=='d' )
	{
		clearScreen();
		movesNo+=gameGrid.move(heroes,myHeroes,answer);
	}
	else if (answer=='I' || answer=='i')
	{
		clearScreen();
		displayInfo();
	}
	else if (answer=='C' || answer=='c')
	{
		if (myHeroes>1)
		{
			clearScreen();
			changeMainHero();
		}
		else
		{
			cout<<"\a";
		}
	}
	else if (answer=='B' || answer=='b')
	{
		clearScreen();
		heroes[mainHero]->checkInventory();
	}
	else if (answer=='E' || answer=='e')
	{
		clearScreen();
		heroes[mainHero]->equip();
	}
	else if (answer=='P' || answer=='p')
	{
		clearScreen();
		heroes[mainHero]->use();
	}
	else if (answer=='M' || answer=='m')
	{
		if (gameGrid.getCurrBlock()->getBlockCond()==market)
		{
			int choice;
			do
			{
				clearScreen();
				cout<<"1.Check shop's menu"<<endl;
				cout<<"2.Buy"<<endl;
				cout<<"3.Sell"<<endl;
				cout<<"4.Exit Shop"<<endl;
				choice=unbufferedInput();
				switch(choice)
				{
					case '1':
					{
						gameGrid.getCurrBlock()->showMenu();
						break;
					}
					case '2':
					{
						gameGrid.getCurrBlock()->buy(heroes[mainHero],mainHero);
						break;
					}
					case '3':
					{
						gameGrid.getCurrBlock()->sell(heroes[mainHero],mainHero);
						break;
					}
					case '4':
					{
						break;
					}
					default:
					{
						cout<<"\a";
						break;
					}
				}
			}while(choice!='4');
		}
		else
		{
			cout<<"\a";
		}
	}
	else if (answer=='K' || answer=='k')
	{
		if (help==true)
			help=false;
		else
			help=true;
	}
	else if (answer=='Q' || answer=='q')
	{
		char exit;
		do
		{
			clearScreen();
			cout<<"Are you sure you want to exit ? (y/n)"; // changed from 2 to 1+ question marks
			exit=unbufferedInput();
			if (exit=='y' || exit=='Y')
			{
				quitGame();
				clearScreen();

			}
			else if (exit!='n' && exit!='N')
			{
				cout<<"\a";
			}
		}while(exit!='y' && exit!='Y' && exit!='n' && exit!='N');
	}
	else
	{
		cout<<"\a";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Grid constructor
Grid::Grid(const database <string> &characterData, const database <class Weapon> &weaponsData,
const database <class Armor> &armorsData, const database <class Potion> &potionsData, const database <class IceSpell> &iceSpellsData,const database <class
FireSpell> &fireSpellsData, const database <class LightningSpell> &lightningSpellsData): map(new block**[width]), currRow(1+rand()%(width-2)),
currColumn(1+rand()%(length-2)), commonProb(0.8), marketProb(0.1), nonAccesibleProb(0.1)
{
	int i;
	for (i=0;i<width;i++)
	{
		map[i]=new block*[length];
	}
	for (i=0;i<width;i++)
	{
		int j;
		for (j=0;j<length;j++)
		{
			double random=double (rand())/RAND_MAX;
			if (i==0 || j==0 || i==width-1 || j==length-1 || (random<nonAccesibleProb && ((currRow==i && currColumn==j)==0)))
				map[i][j]=new nonAccessibleBlock();
			else if (random<commonProb+nonAccesibleProb || (currRow==i && currColumn==j))
				map[i][j]=new commonBlock(characterData);
			else
				map[i][j]=new marketBlock(weaponsData,armorsData,potionsData,iceSpellsData,fireSpellsData,lightningSpellsData);
		}
	}
}

Grid::~Grid()
{
	int i;
	for (i=0;i<width;i++)
	{
		int j;
		for (j=0;j<length;j++)
		{
			delete map[i][j];
		}
	}
	for (i=0;i<width;i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

bool Grid::move(Hero *heroes[], int myHeroes, char move)
{
	bool moved=0;
	if (move=='w' || move=='W')
	{
		if (currRow>0 && map[currRow-1][currColumn]->getBlockCond()!=nonAccessible)
		{
			currRow--;
			moved=1;
		}
	}
	else if (move=='s' || move=='S')
	{
		if (currRow<length-1 && map[currRow+1][currColumn]->getBlockCond()!=nonAccessible)
		{
			currRow++;
			moved=1;
		}
	}
	else if (move=='a' || move=='A')
	{
		if (currColumn>0 && map[currRow][currColumn-1]->getBlockCond() != nonAccessible)
		{
			currColumn--;
			moved=1;
		}
	}
	else if (move=='d' || move=='D')
	{
		if (currColumn<width-1 && map[currRow][currColumn+1]->getBlockCond() !=nonAccessible)
		{
			currColumn++;
			moved=1;
		}
	}
	if (moved)
	{
		if (map[currRow][currColumn]->getBlockCond()==common)
		{
			map[currRow][currColumn]->engageInBattle(heroes,myHeroes);
		}
	}
	else
	{
		cout<<"\a";
	}
	return moved;
}


void Grid::displayMap(Hero *main) const
{
	int i,j;
	cout.width(15);cout<<"MAP"<<endl;
	for (i=0;i<width;i++)
	{
		for (j=0;j<length;j++)
		{
			if (currRow==i && currColumn==j)
			{
				string out;
				out=main->get_name().at(0);
				out+=" ";
				switch (main->get_class())
				{
				case 'W':
					print(out,LIGHT_RED,BOLD);
					break;
				case 'S':
					print(out,MAGENTA,BOLD);
					break;
				case 'P':
					print(out,YELLOW,BOLD);
					break;
				}
			}
			else if (map[i][j]->getBlockCond()==nonAccessible)
			{
				cout<<"* ";
			}
			else if (map[i][j]->getBlockCond()==common)
			{
				cout<<"  ";
			}
			else
			{
				print("M ",GREEN,BOLD);
			}
		}
		cout<<endl;
	}
}

block* Grid::getCurrBlock() const
{
	return map[currRow][currColumn];
}
