#include"graphics.hpp"
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

#ifndef __SPELLS_IN
	#define __SPELLS_IN
	#include "Spells.hpp"
#endif
using namespace std;  
string Living::get_name()const{
    return Name;
}
int Living::get_level()const{
    return level;
}
Living::Living(string N,int l,int HP):level(1),HealthPower(HP),life(1){
  Name=N;
}
int Living::Faint(){
    if(life==0)
       return 1;
    else 
        return 0;
}
void Living::set_life(const int L){
      life=L;
}
void Hero::level_up(){
  clearScreen();
  string msg="Congratulations!!";
  msg+=Name;
  msg+=" leveled up to ";
  if (level<9)
  	msg+=level+1+'0';
  else
  	msg+="10";
    
  print(msg, RED , ITALIC , LIGHT_GREEN);
  cout<<endl;
  cout<<"Press any key to continue...";
  unbufferedInput();
  
  strength+=3;
  agility+=3;
  dexterity+=3;
  level++;
}

Hero::Hero(string N,int l , int HP , int MP,int m):Living(N,l,HP),MagicPower(MP),exp(0),money(m),armor(0),armorInUse(NULL)
{
	weaponsInUse[0]=weaponsInUse[1]=NULL;
    strength=3;                                     

    dexterity=3;

    agility=2;

  W.start=W.tail=NULL;
  P.start=P.tail=NULL;
  A.start=A.tail=NULL;
  I.start=I.tail=NULL;
  F.start=F.tail=NULL;
  L.start=L.tail=NULL;



}
Hero::~Hero(){
        Delete<Weapon>();
        Delete<Potion>();
        Delete<Armor>();
        Delete<IceSpell>();
        Delete<FireSpell>();
        Delete<LightningSpell>();
}
void Hero::displayStats()const{
  int damage=strength,i;
  cout<<"Level : "<<level<<" HealthPower : "<<HealthPower<<" MagicPower : "<<MagicPower<<" Money : "<<money<<endl;
  cout<<"Experience to next level "<<100-exp<<endl;
  cout<<"Strength : "<<strength<<endl;
  cout<<"Dexterity : "<<dexterity<<endl;
  cout<<"Agility : "<<agility<<endl;
  cout<<"Weapons :";
  for(i=0;i<2-get_handsAvailable();i++){
      if(weaponsInUse[i]){
        if(weaponsInUse[i]->getHandsNeeded()==2){
            cout<<weaponsInUse[i]->get_name();
            cout<<" in both hands"<<endl;
            damage+=weaponsInUse[i]->getDamage();
            break;
        }
        if(i==0)
            cout<<"Right Hand : ";
        else 
            cout<<"\t Left Hand : ";
        cout<<weaponsInUse[i]->get_name();
        cout<<endl;
        damage+=weaponsInUse[i]->getDamage();
      }
  } 
  if(damage==strength){
      cout<<"None"<<endl;
  }
  cout<<"Damage : "<<damage<<endl;
  cout<<"Armor : "<<armor<<endl;
  cout<<"Armor Equiped : ";
  if(!armor)
      cout<<"None"<<endl;
  else
      cout<<armorInUse->get_name()<<endl;
}
template<class T>
void Hero::Delete(){
    node<T> *temp,*ptr;
    
    List <T> &TList=get_List<T>();
    temp=TList.start;
    ptr=temp;
    
    while(temp!=NULL){
                ptr =temp;
                temp=temp->next;
                delete ptr;
    }

}
template<class T>
void Hero::Store( T *thing ,int pst ){

  node<T> *temp=new node<T>;

  temp->next=NULL;
  temp->data=thing;
  temp->individuality=pst;
  T::printHeadline();
  cout<<endl;
  thing->printInfo();
  cout<<endl;
  
  temp->next=NULL;
  List <T> &TList=get_List<T>();
	
  if(TList.start==NULL)
  {
	TList.start=TList.tail=temp;
  }
  else
  {
  	    TList.tail->next=temp;
  	    TList.tail=temp;
  }
}

template<class T>
Hero::node<T> *Hero::Find(int j,List<T> P){

  int i=1;

  node<T> *head=P.start;

  node<T> *temp=head;

	while(temp!=NULL && i<j){
    
    temp=temp->next;

    i++;

  }
  return temp;
}

template<class T>
int Hero::Sell(int i,List<T> &P,int &n)	{

  int price;
  
  if (i==1)
  {
  	node<T> *del;
  	del=Find(1,P);
  	price=del->data->getPrice()/2;
  	if (P.start==P.tail)
  		P.tail=NULL;
  		
  	P.start=del->next;
    n=del->get_individuality();	
  	delete del;
  }
  else
  {
  	node<T> *prev, *del;
  	prev=Find(i-1,P);
  	del=prev->next;
  	price=del->data->getPrice()/2;
  	prev->next=del->next;
  	if (del==P.tail)
  		P.tail=prev;
     n=del->get_individuality();	
  	delete del;
  }
  return price;
}

template<>
Hero::List<Weapon>& Hero::get_List(){

     return W;
  
}

template<>
Hero::List<Potion>& Hero::get_List(){
       
     return P;

}

template<>
 Hero::List<Armor>& Hero::get_List(){
   
    return A;

}

template<>
Hero::List<LightningSpell>& Hero::get_List(){
   
    return L;

 }
 
template<>
Hero::List<FireSpell>& Hero::get_List(){
   
    return F;

}
 
template<>
Hero::List<IceSpell>& Hero::get_List(){
   
    return I;

}
template<class T>
int Hero::printList(const List<T> &ptr ){
     int i=1;
     node<T> *head=ptr.start;

      node<T> *temp;
	  
	  if (head==NULL)
	  {
	  	return 0;
	  }
	  else
      {
      	cout.width(4);cout<<"";
	  	T::printHeadline();
	  	cout<<endl;
	  }

      temp=head;
      while(temp!=NULL){
		
      	cout.width(2);cout.fill('0');cout<<right<<i<<". "; cout.fill(' ');       
        temp->data->printInfo();
        cout<<endl;

          temp=temp->next;
          i++;
      }
  return --i;
}



void Hero::checkInventory(){			

  print("INVENTORY",YELLOW,UNDERLINE,RED);
  cout<<endl<<endl;

  print("ITEMS",YELLOW,BOLD,RED);
  cout<<endl;
  
  print("Weapons",YELLOW,NORMAL,RED);
  cout<<endl;  
  printList<Weapon>(W);
  cout<<endl;
  
  print("Potions",YELLOW,NORMAL,RED);
  cout<<endl;
  printList<Potion>(P);
  cout<<endl;
  
  print("Armors",YELLOW,NORMAL,RED);
  cout<<endl;
  printList<Armor>(A);
  cout<<endl<<endl;
  
  print("SPELLS",YELLOW,BOLD,RED);
  cout<<endl;
  
  print("Lightining Spells",YELLOW,NORMAL,RED);
  cout<<endl;
  printList<LightningSpell>(L);
  cout<<endl;

  print("Fire Spells",YELLOW,NORMAL,RED);
  cout<<endl;
  printList<FireSpell>(F);
  cout<<endl;

  print("Ice Spells",YELLOW,NORMAL,RED);
  cout<<endl;
  printList<IceSpell>(I);
  cout<<endl<<endl;
  
  cout<<"Press any key to continue..."<<endl;
  unbufferedInput();
}
void Hero::set_exp(const int i){

    exp=i;

}

int Hero::get_exp()const{

    return exp;

}

void Hero::set_money(const int CurrMoney){

    money=CurrMoney;

}
int Hero::get_money()const{

    return money;

}

int Hero::get_strength()const{

    return strength;

}
void Hero::set_strength(const int newStrength){

          strength=newStrength;

}

int Hero::get_agility()const{

      return agility;

}

void Hero::set_agility(const int newAgility){

        agility=newAgility;

}

int Hero::get_dexterity()const {

      return dexterity;

}

void Hero::set_dexterity(const int newDexterity){

      dexterity=newDexterity;

}

int Hero::get_magicPower()const{

      return MagicPower;

}

void Hero::set_magicPower(const int newMagicPower){

        MagicPower=newMagicPower;

}

int Hero::get_HP()const{

      return HealthPower;

}

void Hero::set_HP(const int newHP){

    HealthPower=newHP;

}

int Hero::get_armor()const{

      return armor;

}
template<class T>
int Hero::node<T>::get_individuality(){
    return individuality;
}
 int  Hero::get_handsAvailable()const{
    int Hands=2;
    for(int i=0;i<2;i++){
      if(weaponsInUse[i]!=NULL)
        if(weaponsInUse[i]->getHandsNeeded()==1){
            Hands--;
        }
        else{
            Hands-=2;
        }
    }
    return Hands;
}

int Hero::attack(Monster **monsters,int MN,int &used){
    int n=0,num=MN;
    int H=get_handsAvailable();
    int damage=strength,damageDealt,chance,i;
    char monster;
    for(i=0;i<(2-H);i++){
      if(weaponsInUse[i]){
        damage+=weaponsInUse[i]->getDamage();
        if(weaponsInUse[0]==weaponsInUse[1]){
            break;
        }
      }
    }
    do
	{
		clearScreen();
        cout<<"Choose which monster you want to attack or "<<MN+1<<" to exit"<<endl;
        for(i=0;i<MN;i++)
		{
        	if(monsters[i])
        		if(monsters[i]->Faint()==0)
        			cout<<i+1<<" "<<monsters[i]->get_name()<<endl;
        		else
        			cout<<i+1<<" "<<monsters[i]->get_name()<<" Already dead"<<endl;
     	}
        monster=unbufferedInput();
        monster-='1';
        if(monster>MN || monster<0)
		{
			cout<<"That monster doesn't exist.Try again. \a"<<endl;
			cout<<"Press any key to continue..."<<endl;
        	unbufferedInput();
        }
        else if (monster!=MN && monsters[monster]->Faint())
        {
        	cout<<"Monster already dead. Try again. \a"<<endl;
        	cout<<"Press any key to continue..."<<endl;
        	unbufferedInput();
        }        
    }while(monster>MN || monster<0 || (monster!=MN && monsters[monster]->Faint()));
    if (monster!=MN)
	{
		used=1;
    	chance=rand()%(100-monsters[monster]->get_evasion());
    	if(chance>10)
		{
    		damageDealt=damage-(monsters[monster]->get_armor());
    	    if(damageDealt<0){
    	        damageDealt=1;
    	    }
    	    cout<<"DIRECT HIT. Dealt "<<damageDealt<<" damage"<<endl;
    	    int newHP=monsters[monster]->get_HP()-damageDealt;
    	    if(newHP<=0){
    	      cout<<"MONSTER DOWN.Good work"<<endl;
    	        monsters[monster]->set_life(0);
    	        monsters[monster]->set_HP(0);
    	        return 1;
    	    }
    	    else{
    	      monsters[monster]->set_HP(newHP);
    	    }
    	}
    	else{
    	    cout<<"Attack Failed"<<endl;
    	}
    	return 0;
    }
    else
    {
    	used=0;
    	return 0;
	}
}

int Hero::use(){
    int number,i;
    List<Potion> &P=get_List<Potion>();
    bool fail;
    do
    {
    	clearScreen();
      	print("Potion List",RED,ITALIC,BLUE);
      	cout<<endl;
      	i=printList(P);
      	if(i==0)
	  	{
	  		cout<<endl<<"You don't have a potion to use"<<endl;
      	  	cout<<"Press any key to continue..."<<endl;
      	  	unbufferedInput();
	  		return 0;
      	}
      	cout<<i+1<<". Back"<<endl;

      	cout<<"Which potion of the above whould you like to use: ";
      	cin >> number;
      	if ((fail=cin.fail())==0)
      	{
      		cin.ignore();
      		if (number<1 || number>i+1)
      		{
      			cout<<"\a";
      			fail=1;
      		}
      	}
     	else
		{
			cout<<"\a";
			cin.clear();
			cin.ignore(100,'\n');
		}		
    }while (fail);
	if (number!=i+1)	
	{
		node<Potion> *prev;
		node<Potion> *temp=Find<Potion>(number,P);
    	Potion *p;
    	p=temp->data;
    	print("You started to drink the potion...",CYAN,ITALIC);
    	cout<<endl;
    	UsePotion(p);
    	if(temp==P.start){
            if(P.start==P.tail){
                P.tail=NULL;
                P.start=NULL;
                delete temp;
            }
        	else{
                P.start=temp->next;
                delete temp;
            }
    	}
      else{
            prev=Find<Potion>(number-1,P);
            prev->next=temp->next;
            if (temp==P.tail)
            {
  		        P.tail=prev;
  	            delete temp;
  	        }
      }
      return 1;
   }
   else
   	  return 0;
}

void Hero::UsePotion(Potion *P){
      statCategory stat;
      stat=P->getStat();
      if(stat==healthPowerStat){
          HealthPower+=(P->getIncreament());
          if(HealthPower>100){
              HealthPower=100;
          }
          print("You feel rejuvenated by the potions effect.Your HP increased ",LIGHT_RED,ITALIC);
          cout<<endl;
            cout<<"Press any key to continue..."<<endl;
            unbufferedInput();
	  	    return;
      }
      else if(stat==strengthStat){
          strength+=P->getIncreament();
          print("You feel stronger than you were before.Your Strength increased ",RED,ITALIC);
          cout<<endl;
          cout<<"Press any key to continue..."<<endl;
            unbufferedInput();
	  	    return;
      }
      else if(stat==agilityStat){
          agility+=P->getIncreament();
          print("You feel your body lighter and your movements quicker.Your agility increased",GREEN,ITALIC);
          cout<<endl;
          cout<<"Press any key to continue..."<<endl;
        unbufferedInput();
	  	return;
      }
      else if(stat==dexterityStat){
        dexterity+=P->getIncreament();
        print("The potions effect raised your intellect.Your dexterity increased",MAGENTA,ITALIC);
        cout<<endl;
        cout<<"Press any key to continue..."<<endl;
        unbufferedInput();
	  	return;
      }
      else if(stat==magicPowerStat){
        MagicPower+=P->getIncreament();
        if(MagicPower>100){
            MagicPower=100;
        }
        print("You feel the essence of magic flow through you.Your MP increased",BLUE,ITALIC);
        cout<<endl;
        cout<<"Press any key to continue..."<<endl;
        unbufferedInput();
	  	return;
      }
}

int Hero::CastSpell(Monster **monsters,int MN,int &used){
    int monster,number,MPspent,MP,damage,damageDealt,decrease,value,currM=0,total,lack=0;
    char s;
    Spell *spell;
    Spell *ptr;
    bool fail=0;
    do{
      clearScreen();
      cout<<"Which type of spell would you like to cast?(F,L,I)"<<endl;
      print("Choose E to Exit");
      cout<<endl;
      s=unbufferedInput();
      if(s=='F'||s=='f'){
      	do{
      		clearScreen();
          	print("Fire",RED,ITALIC);
          	cout<<endl;
          	total=printList(F);
        	if(total==0){
        	  print("You have no Fire Spells",GREEN,ITALIC);
        	  cout<<endl;
        	  lack=1;
        	  cout<<"Press any key to continue..."<<endl;
        	  unbufferedInput();
        	}
        	else
        	{
        		cout<<"Choose the number of the spell you want to cast or "<<(total+1)<<" to exit"<<endl;
        		cin>>number;
        		if ((fail=cin.fail())==0)
        		{
        			cin.ignore();
        			if (number<1 || number>total+1)
					{
						fail=1;
						cout<<"\a";
					}
					else  if (number!=total+1)
					{
       					currM= CastFire(monsters,MN,number,fail);
       					used=(fail==0)?1:0;
       					if (used)
       						return currM;
       				}
       			}
     	  		else
       			{
					cout<<"\a";
					cin.clear();
					cin.ignore(100,'\n');		
	   			}
	   		}
      	}while(fail);
      }
      else if(s=='I'||s=='i'){
      	do
      	{
      		clearScreen();
    		print("ICE",LIGHT_BLUE,ITALIC);
          	cout<<endl;
          	total=printList(I);
        	if(total==0){
        	  print("You have no Ice Spells",GREEN,ITALIC);
        	  cout<<endl;
        	  lack=1;
          	  cout<<"Press any key to continue..."<<endl;
        	  unbufferedInput();
        	}
        	else
			{
        		cout<<"Choose the number of the spell you want to cast or "<<(total+1)<<" to exit"<<endl;
       			cin>>number;
       			if ((fail=cin.fail())==0)
       			{
       				cin.ignore();
          			if (number<1 || number>total+1)
        			{
        				fail=1;
        				cout<<"\a";
					}
					else if (number!=total+1)
					{
						currM= CastIce(monsters,MN,number,fail);
       					used=(fail==0)?1:0;
       					if (used)
       						return currM;
       				}
      			}
      			else
      			{
      				cout<<"\a";
					cin.clear();
					cin.ignore(100,'\n');
				}
      		}
      	}while(fail);
      }
      else if(s=='L'||s=='l'){
      	do
      	{
      		clearScreen();
		  	print("Lightning",YELLOW,ITALIC);
          	cout<<endl;
          	total=printList(L);
        	if(total==0){
        	  print("You have no Lightning Spells",GREEN,ITALIC);
        	  cout<<endl;
        	  lack=1;
          	   cout<<"Press any key to continue..."<<endl;
        	   unbufferedInput();
        	}
        	else
        	{
        		cout<<"Choose the number of the spell you want to cast or "<<(total+1)<<" to exit"<<endl;
        		cin>>number;
        		if ((fail=cin.fail())==0)
        		{
        			cin.ignore();
        			if (number<1 || number>total+1)
        			{
        				fail=1;
        				cout<<"\a";
					}
					else if (number!=total+1)
					{
						currM= CastLightning(monsters,MN,number,fail);
       					used=(fail==0)?1:0;
       					if (used)
       						return currM;
       				}
       			}
       			else
       			{
       				cout<<"\a";
					cin.clear();
					cin.ignore(100,'\n');
				}
			}
		}while(fail);
      }
      else if(s!='E' && s!='e'){
      	cout<<"\a";
	  }
    }while(s!='E' && s!='e');
    return currM;
}
void Monster::refresh(){
    if(spell->get_thing()==FireSpellS){
       armor+=spell->getDrop();
    }
    else if(spell->get_thing()==IceSpellS){
        damage+=spell->getDrop();
    }
    else if(spell->get_thing()==LightningSpellS){
        evasion+=spell->getDrop();
    }
    delete spell;
    spell=NULL;
}
int Hero::CastFire(Monster **monsters,int MN,int number,bool &cancel){
    cancel=0;
	int monster,MPspent,MP,damage,damageDealt,decrease,value,i,currM;
    currM=MN;
    Spell *spell;
    List<FireSpell> &F=get_List<FireSpell>();
    node<FireSpell> *temp=Find<FireSpell>(number,F);
    FireSpell *ptr=temp->data;
    bool illegal;
    do
    {   
    	clearScreen();
		cout<<"Choose which monster do you want to attack or "<< MN+1<<" to cancel"<<endl;
		for(i=0;i<MN;i++)
		{
        	if(monsters[i]->Faint()==0)
        		cout<<i+1<<" "<<monsters[i]->get_name()<<endl;
        	else
          		cout<<i+1<<" "<<monsters[i]->get_name()<<" DEAD "<<endl;
      	}
      	cout<<MN+1<<" "<<"back"<<endl;
        cin>>monster;
        if ((illegal=cin.fail())==0)
        {
        	cin.ignore();
        	monster--;
        	if(monster>MN || monster<0)
        	{
        		cout<<"\a";
        		illegal=1;
        	}
			else if (monster!=MN && monsters[monster]->Faint())
			{
            	cout<<"This monster is dead ,try again"<<endl;
            	illegal=1;
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
    }while (illegal);
    if (monster!=MN)
    {
    	MP=get_magicPower();
    	MPspent=ptr->getMagicEnergyReq();
        if((MP-MPspent)<0){
            cout<<"You are out of MP \n";
            cancel=1;
            cout<<"Press any key to continue..."<<endl;
            unbufferedInput();
            return 0;
        }
    	set_magicPower(MP-MPspent);
    	damage=ptr->getDamage(get_dexterity());
    	damageDealt=damage-(monsters[monster]->get_armor());
    	if(damageDealt<0){
    	    damageDealt=1;
    	}
    	cout<<endl<<"You scorched your enemies dealing "<<damageDealt<<" and reducing their armor by "<<ptr->getDrop()<<endl;
    	int newHP=monsters[monster]->get_HP()-damageDealt;
    	if(newHP<=0){
    	    cout<<"Monster burned to death.Good work. \n";
    	    monsters[monster]->set_HP(0);
    	    monsters[monster]->set_life(0);
    	    return 1;
    	}
    	else{
    	    monsters[monster]->set_HP(newHP);
    	}
    	spell=monsters[monster]->get_affliction();
    	if(spell!=NULL){
            spell= new FireSpell(*ptr);
            monsters[monster]->refresh();
        }
        else{
            spell= new FireSpell(*ptr);
        }
        decrease=ptr->getDrop();
        monsters[monster]->set_affliction(spell);
        value=monsters[monster]->get_armor();
        if(value>decrease)
          monsters[monster]->set_armor(value-decrease);
         else
            monsters[monster]->set_armor(0);
        return 0;
	}
	else
	{
		cancel=1;
		return 0;
	}
}

int Hero::CastIce(Monster **monsters,int MN,int number, bool &cancel){
	cancel=0;
    int monster,MPspent,MP,damage,damageDealt,decrease,value,i,currM;
    currM=MN;
    Spell *spell;
    IceSpell *ptr;
    List<IceSpell> &I=get_List<IceSpell>();
    node<IceSpell> *temp=Find<IceSpell>(number,I);
    ptr=temp->data;
    bool illegal;
    do
    {   
    	clearScreen();
		cout<<"Choose which monster do you want to attack or "<< MN+1<<" to cancel"<<endl;
		for(i=0;i<MN;i++)
		{
        	if(monsters[i]->Faint()==0)
        		cout<<i+1<<" "<<monsters[i]->get_name()<<endl;
        	else
          		cout<<i+1<<" "<<monsters[i]->get_name()<<" DEAD "<<endl;
      	}
      	cout<<MN+1<<" "<<"back"<<endl;
        cin>>monster;
        if ((illegal=cin.fail())==0)
        {
        	cin.ignore();
        	monster--;
        	if(monster>MN || monster<0)
        	{
        		cout<<"\a";
        		illegal=1;
        	}
			else if (monster!=MN && monsters[monster]->Faint())
			{
            	cout<<"This monster is dead ,try again"<<endl;
            	illegal=1;
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
    }while (illegal);
    if (monster!=MN)
    {
    	MP=get_magicPower();
    	MPspent=ptr->getMagicEnergyReq();
        if((MP-MPspent)<0){
            cout<<"You are out of MP \n";
            cancel=1;
            cout<<"Press any key to continue..."<<endl;
            unbufferedInput();
            return 0;
        }
    	set_magicPower(MP-MPspent);
    	damage=ptr->getDamage(get_dexterity());
        damageDealt=damage-(monsters[monster]->get_damage());
        if(damageDealt<0){
                damageDealt=1;
        }
        cout<<endl<<"You froze your enemies dealing "<<damageDealt<<" and reducing their damage by "<<ptr->getDrop()<<endl;
        int newHP=monsters[monster]->get_HP()-damageDealt;
        if(newHP<=0){
            cout<<"Monster froze to death.Good work. \n";
              monsters[monster]->set_HP(0);
               monsters[monster]->set_life(0);
               return 1;
        }
        else{
          monsters[monster]->set_HP(newHP);
        }
        spell=monsters[monster]->get_affliction();
         if(spell!=NULL){
            delete spell;
            spell= new IceSpell(*ptr);
            monsters[monster]->refresh();
        }
        else{
            spell= new IceSpell(*ptr);
        }
        decrease=ptr->getDrop();
        monsters[monster]->set_affliction(spell);
         value=monsters[monster]->get_damage();
         if(value>decrease)
          monsters[monster]->set_damage(value-decrease);
         else{ 
            monsters[monster]->set_damage(0);
        }
        return 0;
    }
    else
    {
    	cancel=1;
    	return 0;
	}
}

int Hero::CastLightning(Monster **monsters,int MN,int number,bool &cancel){
	cancel=0;
    int monster,MPspent,MP,damage,damageDealt,decrease,value,i,currM;
    Spell *spell;
    currM=MN;
    List<LightningSpell> &L=get_List<LightningSpell>();
    node<LightningSpell> *temp=Find<LightningSpell>(number,L);
    LightningSpell *ptr=temp->data;
    bool illegal;
    do
    {   
    	clearScreen();
		cout<<"Choose which monster do you want to attack or "<< MN+1<<" to cancel"<<endl;
		for(i=0;i<MN;i++)
		{
        	if(monsters[i]->Faint()==0)
        		cout<<i+1<<" "<<monsters[i]->get_name()<<endl;
        	else
          		cout<<i+1<<" "<<monsters[i]->get_name()<<" DEAD "<<endl;
      	}
      	cout<<MN+1<<" "<<"back"<<endl;
        cin>>monster;
        if ((illegal=cin.fail())==0)
        {
        	cin.ignore();
        	monster--;
        	if(monster>MN || monster<0)
        	{
        		cout<<"\a";
        		illegal=1;
        	}
			else if (monster!=MN && monsters[monster]->Faint())
			{
            	cout<<"This monster is dead ,try again"<<endl;
            	illegal=1;
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
    }while (illegal);
    if (monster!=MN)
    {
      MP=get_magicPower();
      MPspent=ptr->getMagicEnergyReq();
      if((MP-MPspent)<0){
            cout<<"You are out of MP \n";
            cancel=1;
            cout<<"Press any key to continue..."<<endl;
            unbufferedInput();
            return 0;
        }
      set_magicPower(MP-MPspent);
      damage=ptr->getDamage(get_dexterity());
        damageDealt=damage-(monsters[monster]->get_armor());
         if(damageDealt<0){
                damageDealt=1;
        }
        cout<<endl<<"You zapped your enemies dealing "<<damageDealt<<" and reducing their evasion by "<<ptr->getDrop()<<endl;
        int newHP=monsters[monster]->get_HP()-damageDealt;
        if(newHP<=0){
         cout<<"Monster electrocuted to death.Good work. \n";
              monsters[monster]->set_HP(0);
               monsters[monster]->set_life(0);
               return 1;
        }
        else{
          monsters[monster]->set_HP(newHP);
        }
        spell=monsters[monster]->get_affliction();
        decrease=ptr->getDrop();
        if(spell!=NULL){
            spell= new LightningSpell(*ptr);
            monsters[monster]->refresh();
        }
        else{
            spell= new LightningSpell(*ptr);
        }
        monsters[monster]->set_affliction(spell);
            value=monsters[monster]->get_evasion();
            if(value>decrease)
                monsters[monster]->set_evasion(value-decrease);
            else{ 
                monsters[monster]->set_evasion(0);
            }
            return 0;
    }
    else
    {
    	cancel=1;
    	return 0;
	}
}

int Hero::addArmor(const Armor *ptr){
    if(armorInUse==NULL){
        armorInUse=ptr;
        armor=ptr->getDamageReduction();
        cout<<endl;
        print("Succesfully equiped armor",RED,ITALIC);
        cout<<endl;
        cout<<"Press any key to continue..."<<endl;
        unbufferedInput();
        return 1;
    }
    else return 0;
}
int  Hero::removeArmor(){
    if(armorInUse){
        set_armor(0);
       armorInUse=NULL;
        return 1;
    }
    else{return 0;}
}
int Hero::removeWeapon(int i=1){
  if(i-1<2){
    if(weaponsInUse[0]==weaponsInUse[1]){
      weaponsInUse[1]=NULL;
      weaponsInUse[0]=NULL;
      return 1;
    }
    else{
        weaponsInUse[i-1]=NULL;
    }
  }
  else{
    return 0;
  }
}
int Hero::addWeapon(const Weapon *ptr){

  if(ptr->getHandsNeeded()==2){
    for(int i=0;i<2;i++){
      if(weaponsInUse[i]!=NULL){
          return 0;
      }
    }
    weaponsInUse[0]=ptr;
    weaponsInUse[1]=weaponsInUse[0];
    cout<<endl;
    print("Succesfully equiped weapon in both hands",RED,ITALIC);
    cout<<endl;
    cout<<"Press any key to continue..."<<endl;
    unbufferedInput();
    return 1;
  }
 else
  for(int i=0;i<2;i++){
      if(weaponsInUse[i]==NULL){
          weaponsInUse[i]=ptr;
          if(i==0)
                print("Succesfully equiped weapon in right hand",RED,ITALIC);
          else
                print("Succesfully equiped weapon in left hand",RED,ITALIC);
           cout<<endl<<"Press any key to continue..."<<endl;
            unbufferedInput();
          return 1;
          
      }
  }
  return 0;

}
int Hero::equip(){
    char choice;
    int value=0;
    do
    {
    	clearScreen();
    	cout<<"1.Change Armor"<<endl;
		cout<<"2.Change Weaponry"<<endl;
		cout<<"3.Back"<<endl;
    	choice=unbufferedInput();
    	if(choice=='1'){
    	   value=this->changeArmor();
    	}
    	else if(choice=='2'){
    	    value=this->changeWeapon();
    	}
    	else if (choice!='3')
		{
    		cout<<"\a";
		}
	}while (choice!='3');
    return value;
}
int Hero::changeWeapon()
{
	int i,number,used=0,total;
    bool wrong;

	Weapon *temp;
    
    do
    {
        wrong=0;
        clearScreen();
	    cout<<"Weapon(s) in use"<<endl;
        if (get_handsAvailable()==2)
    	    cout<<": none"<<endl;
        else
	    {
		    cout<<endl;
		    cout.width(3);cout<<""; 
		    	if (weaponsInUse[0]!=NULL){
                    cout<<endl;
            		cout<<"Right Hand :";
                    cout<<weaponsInUse[0]->get_name()<<endl;
                }
                else{
                    cout<<"Free right hand"<<endl;
                }
                if (weaponsInUse[1]!=NULL){
                    cout<<endl;
            		cout<<"Left Hand :";
                    cout<<weaponsInUse[1]->get_name()<<endl;
                }
                else{
                    cout<<"Free left hand"<<endl;
                }
	    }
        total=printList(W);
        if(!total){
            print("No weapons to equip",RED,ITALIC);
            cout<<endl;
        }
        cout.width(3);cout.fill('0');cout<<right<<total+1<<". Back"<<endl;cout.fill(' ');
    	print("List choice",RED,ITALIC,LIGHT_GREEN);
        cout<<endl;
        cin>>number;
        if ((wrong=cin.fail())==0){
        		cin.ignore();
            	if(number==(total+1)){
               	 return 0;
            	}
    			if (number<1 || number>total+1)
    				cout<<"\a";
            	else{
            	    used=0;
            	   temp=Find<Weapon>(number,W)->data;
                for(i=0;i<2;i++){
                    if(weaponsInUse[i]!=NULL && temp==weaponsInUse[i]){
                        cout<<"Weapon already in use."<<endl;
                        used=1;
                    }
                } 
        	}
        }
        	else
        	{
        		cout<<"\a";
				cin.clear();
				cin.ignore(100,'\n');
			}
		}while(wrong || number<1 || number>total+1 || used);
    	if(!addWeapon(temp)){
            if(weaponsInUse[0]==weaponsInUse[1]){
                cout<<"Removing Dual-Wielded weapon"<<endl;
                removeWeapon();
    	        addWeapon(temp);
                return 1;
            }
                if(temp->getHandsNeeded()==2){
                    cout<<"Removing both weapons";
                    removeWeapon(1);
                    removeWeapon(2);
    	            addWeapon(temp);
                    return 1;
                }
    	        cout<<endl<<"Which weapon do you want to remove,the 1st or the 2nd"<<endl;
    	        cin>>number;
                removeWeapon(number);
    	        addWeapon(temp);
        } 
        else{
            return 1;
        }
        return 0;
}

int Hero::changeArmor(){
  int i,number,used=0,totalArmors;
  bool fail;
    char c;
   Armor *temp;
		do{
            clearScreen();
            cout<<"Armor in use";
            if (armorInUse==NULL){
    	        cout<<": none"<<endl;
	        }
	        else{
		        cout<<endl;
    	        cout<<armorInUse->get_name();
                 cout<<endl;
	        }
            cout<<"List of armors"<<endl;
	        totalArmors=printList<class Armor>(A);
	        if(!totalArmors){
                print("No armor to equip",BLUE,ITALIC);
                cout<<endl;
            }
            cout<<totalArmors+1<<"."<<" to Exit"<<endl;
			print("List choice",RED,ITALIC,LIGHT_GREEN);
            cout<<endl;
    		cin>>number;
    		if ((fail=cin.fail())==0)
    		{
    			cin.ignore();
            	if(number==(totalArmors+1)){
               	 return 0;
            	}
    			if (number<1 || number>totalArmors+1)
    				cout<<"\a";
            	else{
            	    used=0;
            	    temp=Find<Armor>(number,A)->data;
            	        if(armorInUse!=NULL && temp==armorInUse){
               	         cout<<"Armor already in use."<<endl;
               	         used=1;
               	         cout<<"Press any key to continue...";
               	         unbufferedInput();
               	     }
            	}
        	}
        	else
        	{
        		cout<<"\a";
				cin.clear();
				cin.ignore(100,'\n');
			}
		}while(fail || number<1 || number>totalArmors+1 || used);
		if (number!=totalArmors+1)
		{
    	 if(!addArmor(temp)){
    	   cout<<"Do you want to remove your armor?(y/n)";
    	   do{
    	   		c=unbufferedInput();
    	   		if(c=='Y'||c=='y'){
    	     		removeArmor();
    	     		addArmor(temp);
              		return 1;
    	   		}
    	   		else if (c!='N' && c!='n')
    		 		cout<<"\a";
    		}while(c!='n' && c!='N');
     	 }
         else{
             return 1;
         }
		}
    return 0;
}

void Hero::withdrawWeapon(Weapon* cmp)
{
	while (weaponsInUse[0]==cmp)
	{
		weaponsInUse[0]=weaponsInUse[1];
		weaponsInUse[1]=NULL;
	}
	if (weaponsInUse[1]==cmp)
		weaponsInUse[1]=NULL;
}

void Hero::withdrawArmor(Armor *cmp)
{
	if (armorInUse==cmp)
	{
		armorInUse=NULL;
		armor=0;
	}
}

Warrior::Warrior(string N,int l , int HP , int MP,int m):Hero(N,l,HP,MP,m){
    strength+=3;
    agility+=2;
}
void Warrior::displayStats()const{
  cout<<endl<<"Player : "<<Name<<"   Class : ";
  print("Warrior",LIGHT_RED,ITALIC);
  cout<<endl;
  Hero::displayStats();
}
void Warrior::level_up(){
  Hero::level_up();
  strength+=3;
  agility+=2;
}
char Warrior::get_class()const{

        return 'W';

}
void Sorcerer::displayStats()const{
  cout<<endl<<"Player : "<<Name<<"   Class : ";
  print("Sorcerer",MAGENTA,ITALIC);
  cout<<endl;
  Hero::displayStats();
}
void Sorcerer::level_up(){
  Hero::level_up();
  dexterity+=3;
  agility+=2;
}
Sorcerer::Sorcerer(string N,int l , int HP , int MP,int m):Hero(N,l,HP,MP,m){
    dexterity+=3;
    agility+=3;
}
char Sorcerer::get_class()const{

        return 'S';

}

void Paladin::displayStats()const{
  cout<<endl<<"Player : "<<Name<<"   Class : ";
  print("Palladin",YELLOW,ITALIC);
  cout<<endl;
  Hero::displayStats();
}

void Paladin::level_up(){
  Hero::level_up();
  dexterity+=3;
  strength+=3;
}
Paladin::Paladin(string N,int l , int HP , int MP,int m):Hero(N,l,HP,MP,m){
    dexterity+=3;
    strength+=3;
}
char Paladin::get_class()const{

        return 'P';

}
void Dragon::displayStats()const{
    cout<<endl;
    print("The Legendary Dragon ",RED,ITALIC);
    cout<<Name<<" Health "<<HealthPower<<endl;
    cout<<"Dragon level : "<<level<<endl;
      cout<<"Damage done : "<<damage<<endl;
      cout<<"Armor : "<<armor<<endl;
      cout<<"Evasion : "<<evasion<<endl;

}
Monster::Monster(string N,int l, int HP):Living(N,l,HP){
    damage=level*4;
    armor=level*4;
    evasion=level*4;
    spell=NULL;
}
Monster::~Monster(){
    if(spell!=NULL){
            delete spell;
    }
}
void Exoskeleton::displayStats()const{
    cout<<endl;
    print("The Fearsom Exoskeleton ",DARK_GRAY,ITALIC);
    cout<<Name<<" Health "<<HealthPower<<endl;
    cout<<"Exoskeleton level : "<<level<<endl;
      cout<<"Damage done : "<<damage<<endl;
      cout<<"Armor : "<<armor<<endl;
      cout<<"Evasion : "<<evasion<<endl;

}
void Spirit::displayStats()const{
      cout<<endl;
      print("The Haunting Spirit ",LIGHT_GRAY,ITALIC);
      cout<<Name<<" Health "<<HealthPower<<endl;
      cout<<"Spirit level : "<<level<<endl;
      cout<<"Damage done : "<<damage<<endl;
      cout<<"Armor : "<<armor<<endl;
      cout<<"Evasion : "<<evasion<<endl;

}
int Monster::attack(Hero **heroes,int HN){
    int num=HN;
    int chance,hero,i,damageDealt;
    cout<<endl<<Name<<" Attacks ";
    while(1){
      hero=rand()%HN;
      if(heroes[hero]->Faint()==0)
        break;
      else if(num==1){
          return 0;
      }
    }
    cout<<heroes[hero]->get_name()<<endl;
    chance=rand()%(100-heroes[hero]->get_evasion());
    if(chance>10){
        damageDealt=damage-(heroes[hero]->get_armor());
        if(damageDealt<0){
            damageDealt=1;
        }
        cout<<"\nOUCH. "<<damageDealt<<" damage inflicted \n"<<endl;
        int newHP=heroes[hero]->get_HP()-damageDealt;
        if(newHP<=0){
            heroes[hero]->set_life(0);
            heroes[hero]->set_HP(0);
            return 1;
        }
        else{
          heroes[hero]->set_HP(newHP);
        }
    }
    else{
        cout<<"\n Attack Failed"<<endl;
    }
    return 0;
}
int Monster::get_HP()const{

      return HealthPower;

}

void Monster::set_HP(const int newHP){

    HealthPower=newHP;

}

int Monster::get_evasion()const{

      return evasion;

}

void Monster::set_evasion(const int i){

      evasion=i;

}

int Monster::get_damage()const{

      return damage;

}

void Monster::set_damage(const int i){

      damage=i;

}

int Monster::get_armor()const{

      return armor;

}



void Monster::set_armor(const int i){

      armor=i;

}

Spell *Monster::get_affliction(){

      return spell;

}
void  Monster::set_affliction(class Spell *s){
        
        spell=s; 

}
Dragon::Dragon(string N,int l, int HP):Monster(N,l,HP){
    damage+=3;
}

Exoskeleton::Exoskeleton(string N,int l, int HP):Monster(N,l,HP){
    armor+=3;
}

Spirit::Spirit(string N,int l, int HP):Monster(N,l,HP){
    evasion+=3;
}

template int Hero::Sell<Weapon>(int i,List<Weapon> &P,int &n);
template int Hero::Sell<Potion>(int i,List<Potion> &P,int &n);
template int Hero::Sell<Armor>(int i,List<Armor> &P,int &n);
template int Hero::Sell<LightningSpell>(int i,List<LightningSpell> &P,int &n);
template int Hero::Sell<FireSpell>(int i,List<FireSpell> &P,int &n);
template int Hero::Sell<IceSpell>(int i,List<IceSpell> &P,int &n);
template void Hero::Store<Weapon>(Weapon*,int);
template void Hero::Store<Potion>(Potion*,int);
template void Hero::Store<Armor>(Armor*,int);
template void Hero::Store<LightningSpell>(LightningSpell*,int);
template void Hero::Store<FireSpell>(FireSpell*,int);
template void Hero::Store<IceSpell>(IceSpell*,int);
