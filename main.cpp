//FILE:main.cpp
#ifndef __FSTREAM_IN
	#include <fstream>
	#define __FSTREAM_IN
#endif

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif

#ifndef __CTIME_IN
	#define __CTIME_IN
	#include <ctime>
#endif

#ifndef __CSTDLIB_IN
	#include <cstdlib>
	#define __CSTDLIB_IN
#endif	

#ifndef __GAMING_SYS_IN
	#define __GAMING_SYS_IN
	#include "GamingSystem.hpp"
#endif

using namespace std;

int getNamesNo(ifstream &currFile);
void storeNames(ifstream &currFile, string *namesArray, int namesNo);


int main()
{
	srand(time(NULL));
	char file[7][20]={"CharacterNames.txt","Weapons.txt","Armors.txt","Potions.txt","FireSpells.txt","IceSpells.txt","LightningSpells.txt"};
	string *namesArray[7];
	int namesNo[7];
	int i;
	for (i=0;i<7;i++)
	{
		ifstream currFile(file[i]);
		if (currFile.is_open() == 0)
		{
			cout<<"Error while opening "<<file<<"."<<endl;
			return -1;
		}
		namesNo[i]=getNamesNo(currFile);
		namesArray[i]=new string[namesNo[i]];
		storeNames(currFile, namesArray[i], namesNo[i]);
		currFile.close();
	}
	Game newGame(namesArray,namesNo);
	while (newGame.isActive())
	{
		newGame.chooseAction();
	}
	for(i=0;i<7;i++)
	delete[] namesArray[i];
	return 0;
}

int getNamesNo(ifstream &currFile)
{
	int names=0;
	while (currFile.eof()==0)
	{
		if (currFile.get()=='\n')
			names++;
	}
	return names;
}

void storeNames(ifstream &currFile, string *namesArray, int namesNo)
{
	int i;
	currFile.clear();
	currFile.seekg(0);
	for (i=0;i<namesNo;i++)
	{
		getline(currFile,namesArray[i]);
	}
}
