#pragma once
#include <iostream>
#include <fstream>

using namespace std; 

//Constants

//Structs - 

/*
*  This structure provides the data organization for
*  the year record. It contains:
*  - year as an int
*  - c-string character array for event description
*  - population as an int, in 1000's
* 
* a year is 209 bytes
* 
*/
struct Year {  
	int year; // This is the year for this record
	char event[201]; // supports up to 200 chars, plus null char
	int population; // this is a number of world population, in 1000's. 
};

//functions

char menu();
long inMemory(int);
char again();
int valid();
void showYear(fstream &history);
void changeRecord(fstream &history);
void showPopulation(fstream &history);
void showEvent(fstream &history);
