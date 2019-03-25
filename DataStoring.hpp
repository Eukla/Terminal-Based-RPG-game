//FILE: dataStoring.hpp

#ifndef __IOSTREAM_IN
	#define __IOSTREAM_IN
	#include <iostream>
#endif

#ifndef __STRING_IN
	#define __STRING_IN
	#include <string>
#endif

#ifndef __ENUM_IN
	#define __ENUM_IN
	#include "Enums.hpp"
#endif


template<class T>
struct database
{
	T** const obj;
	const int size;
	bool *available[3];
	
	database(std::string * const names, const int newSize);
	~database();
};

template <>
struct database <std::string>
{
	std::string* const obj;
	const int size;
	bool *available;
	
	database(std::string * const names, const int newSize);
	~database();
};


