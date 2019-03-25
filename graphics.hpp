//FILE:graphics.hpp
#include <string>

enum style{NORMAL,BOLD,FAINT,ITALIC,UNDERLINE};
enum colour{BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,LIGHT_GRAY,DEFAULT=39,DARK_GRAY=90,LIGHT_RED,LIGHT_GREEN,LIGHT_YELLOW,LIGHT_BLUE,
LIGHT_MAGENTA,LIGHT_CYAN,WHITE}; 

//the ANSII colour codes are terminal specific
//tested on the di's linux machines 

void clearScreen();
void print(const std::string str, colour myColour=DEFAULT, style myStyle=NORMAL, colour myBackground=DEFAULT);
char unbufferedInput();
