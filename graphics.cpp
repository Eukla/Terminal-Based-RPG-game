//FILE:graphics.cpp
#include <iostream>
#include "graphics.hpp"
#include <unistd.h>
#include <termios.h>

using namespace std;

void clearScreen()
{
	cout << "\033[2J\033[1;1H";
}

void print(const string str, colour myColour, style myStyle, colour myBackground)
{
	cout<<"\033["<<myStyle<<";"<<myColour<<";"<<myBackground+10<<"m"<<str<<"\033[0m";
	cout<<"\033["<<NORMAL<<";"<<DEFAULT<<"m"<<"\033[0m";
}

char unbufferedInput()				//POSIX compatible OS
{
	
    termios term;							//struct termios contains all the info regarding a terminal interface 
    tcgetattr(STDIN_FILENO,&term);			//gets the terminal's parameters regarding input(STDIN_FILENO) and stores them in term structure
    term.c_lflag &=  ~(ICANON | ECHO);		//turn off echo(ECHO) and canonical(ICANON) mode
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);	//sets the terminal's parameters regarding input(STDIN_FILENO) from the term structure 
    char c=cin.get();						//read a single character
    term.c_lflag |= (ICANON | ECHO);		//turn on echo and cannonical mode
    tcsetattr(STDIN_FILENO,TCSANOW,&term);	//restore the terminal parameters as they were before the function call
    return c;
}

