#include<iostream>

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif

#define __MAXLEVEL 10
#define __DEXTERITY_SCALLING 6
#define __STRENGTH_SCALLING 6
#define __AGILITY_SCALLING 6
using namespace std;
class Item;
class Weapon;
class Armor;
class Spell;
class LightningSpell;
class IceSpell;
class FireSpell;
class Monster;	
class Living{


  protected:

    int level;

    string Name;

    int HealthPower;

    Living(string N,int l,int HP);

    int life;
  public:

    int Faint();

    void set_life(const int);	

    string get_name()const;	

    int get_evasion()const{};

    void set_armor(const int){};
    
    int get_level()const;
    
    void virtual refresh(){
	
    }
   
};
 

class Hero: public Living{

	protected:
    int money;

	private:
    class Weapon  const *weaponsInUse[2];

    class  Armor const *armorInUse;


template<class T>
 class node
    {
       public:
      	  T *data;

      	  node *next;
	 
          int individuality;

	  int get_individuality();
    };
template<class T>
   class List
      {
       public:
         node<T> *start;

         node<T> *tail;
  };  


      class List<class Weapon> W;

      class List<class Potion> P;

      class List<class Armor> A;

      class List<class IceSpell> I;

      class List<class FireSpell> F;
 
      class List<class LightningSpell> L;


  protected:
	
    int armor;		

    int MagicPower;

    int exp;

    int strength;                                     

    int agility;                                       

    int dexterity;

    Hero(string N,int l , int HP , int MP,int m);                			

  public:

  int use();

  ~Hero();
  template<class T>	
  void Delete();
  
  void withdrawWeapon(Weapon* cmp);
  void withdrawArmor(Armor *cmp);

  virtual char get_class()const=0;

	template<class T>	
	List<T>& get_List();

  virtual void displayStats()const;

  int CastSpell(Monster **monsters,int MN,int &used);
	int CastFire(Monster **monsters,int MN,int number,bool &fail);
	int CastIce(Monster **monsters,int MN,int number, bool &fail);
	int CastLightning(Monster **monsters,int MN,int number, bool &fail);

	

  template<class T>
  void Store( T* ,int pst);

  template<class T>
 	int Sell(int i,List<T>&,int&);						
	
  template<class T>
	node<T> *Find(int i,List<T>);

  int changeArmor();
  int addArmor(const class Armor *);
	int removeArmor();

	int attack(Monster**,int MN,int &used);
	int equip();
  int changeWeapon();
  int addWeapon(const class Weapon *);
	int removeWeapon(int);

	int get_handsAvailable() const;	 					

	int get_strength() const;							
	void set_strength(const int newStrength);			
	
	int get_HP()const;
	void set_HP(const int);
	
	int get_armor()const;	
	
	int get_agility() const;							
	void set_agility(const int newAgility);				

	int get_dexterity() const;							
	void set_dexterity(const int newDexterity);			

	int get_magicPower() const;							
	void set_magicPower(const int newMagicPower);		

  void set_exp(const int i);
  int get_exp()const;

  void set_money(const int i);
  int get_money()const;

	void UsePotion(class Potion *);

  virtual void level_up();
  
  void checkInventory();			
  template<class T>
  int printList(const List<T> &ptr);
};

class Warrior: public Hero{

public:

  void level_up();

  void displayStats()const;

  char get_class()const;

  Warrior(string N,int l , int HP , int MP,int m);

};

class Sorcerer: public Hero{

public:

  void level_up();

  void displayStats()const;

  char get_class()const;

  Sorcerer(string N,int l , int HP , int MP,int m);

};

class Paladin: public Hero{

public:

  void level_up();

  void displayStats()const;

  char get_class()const;

  Paladin(string N,int l , int HP , int MP,int m);

  ~Paladin();

};
class Monster: public Living{

  protected:

    int damage;

    int armor;          

    int evasion;

     class Spell *spell;

      Monster(string N,int l, int HP);
 
  public:

    ~Monster();
  
  class Spell *get_affliction();

  void set_affliction(class Spell *);

  int attack(Hero** array,int HN);

  int get_HP()const;
  void set_HP(const int );

  int get_evasion()const;
  void set_evasion(const int);

  int get_armor()const;
  void set_armor(const int);

  int get_damage()const;
  void set_damage(const int);
	
  void refresh();
		
  virtual void displayStats()const{};  

};

class Dragon: public Monster{

  public:

  void displayStats()const;

  Dragon(string N,int l, int HP);
	 
};

class Exoskeleton: public Monster{

  public:

  void displayStats()const;

  Exoskeleton(string N,int l, int HP);

};

class Spirit: public Monster{

  public:
  
  void displayStats()const;

  Spirit(string N,int l, int HP);

};
