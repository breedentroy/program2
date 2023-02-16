#include "history.h"
/**********************************************
 *  Name: Troy Breeden
 *  File Name: historyFunctions.cpp
 *  Description: holds functions
 **********************************************/

// put your functions here. 

/* name menu
 * purpose to allow the user to pick which function to call
 * peramitures none
 * return char coice
 */
char menu() {

	char choice;//how the progam will know what the user wants to do


	cout << "Press 1 to view year\n";//funtion 1 view the event and population of a user given year
	cout << "Press 2 to view population between two years\n";// function 2 show the population for all the years between user's choise
	cout << "Press 3 to alter records\n";//function 3 user can change records
	cout << "press 4 to view events between two years\n";//function 4 show the events between years of the user's choice
	cout << "press any other key to exit\n";//close the program
	cin >> choice;//what the user picks (their nose)
	return choice;

}

/* name inMemory
 * purpose to move to the correct place in history
 * peramitures int inPutYear the year the user chose
 * return long offSet
 */
long inMemory(int inPutYear) {
	long offSet;//what Year in worldHistory.dat to jump to
	offSet = (inPutYear - 1950) ;//the year they entered minus first posible year times the size of a year struct
	return sizeof(Year)* offSet;
}

/* name again
 * purpose to ask the user if they are finished with the program
 * peramitures none
 * return char returnToMenu
 */
char again() {
	
	char returnToMenu;//Does the user want to return to menu?

	cout << "Would you like to return to menu? (to use function again you must go to menu)\n";//dose the user want do anything else
	cout << "y/n       ";
	cin >> returnToMenu;
	return returnToMenu;

}

/* name valid
 * purpose to ensure that user inputs a year that is in the record
 * peramitures none
 * return int what year
 */
int valid() {
	bool valid;// is the user's year in the data base
	int whatYear;//the year the user enters

	do {//if the use enters a wrong year promt them for a new one
		cin >> whatYear;
		if (whatYear < 1950 || whatYear>2020) {
			valid = false;
			cout << "please enter a valid year\n";
		}
		else {
			valid = true;
		}
	} while (!valid);
	return whatYear;
}

/* name showYear
 * purpose to show the user the info for the year they chose
 * peramitures address of the fstream history
 * return void
 */
void showYear(fstream &history) {
	int whatYear;//what year does the user want
	long offSet;//which member of Year
	Year yearRecord;//holds data from worldhistory.dat

	/*fstream history;
	history.open("worldHistory.dat", ios::in | ios::binary);*/

	cout << "What year would you like to know the event and population of? (1950 - 2020)\n";//tells the user the limits

	whatYear = valid();

	//go to year display population and event
	offSet = inMemory(whatYear);
	
	history.seekg(offSet, ios::beg); 
	history.read(reinterpret_cast<char*>(&yearRecord), sizeof(Year));
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << fixed << setprecision(2) << setw(4) << static_cast<double>(yearRecord.population)/1000000 << endl << endl;

}

/* name change record
 * purpose to allow the user to modify worldHistory.dat in the year they selected
 * peramitures address of the fstream history
 * return void
 */
void changeRecord(fstream &history) {
	int whatYear;//what year does the user want to modify
	long offSet;//which member of Year
	string newEvent;// the users new evet for the year.
	int newPopulation;// the users new population
	Year yearRecord;//holds data from worldhistory.dat

	cout << "What year would you like to modify the event and population of? (1950 - 2020)\n";//tells the user the limits

	whatYear = valid();
	    
	//go to year display population and event
	offSet = inMemory(whatYear);
	history.seekg(offSet, ios::beg); 
	history.seekp(offSet, ios::beg);

	
	history.read(reinterpret_cast<char*>(&yearRecord), sizeof(Year));//remind the user what the record curently says
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << fixed << setprecision(2) << setw(4)  << static_cast<double>(yearRecord.population) << endl << endl;
	

	cout << "what new event happened in " << yearRecord.year << "? (enter \"NOTHING NEW\" to leave unchanged)\n";
	//cin >> newEvent;
	cin.ignore();
	getline(cin, newEvent); 
	if (!newEvent._Equal("NOTHING NEW")) {//offer to leave event unchanged
		strcpy_s(yearRecord.event,200, newEvent.c_str());//change the record
	}
	
	cout << "\nwhat was the new population in " << yearRecord.year << "? (enter a negitive number to leave unchanged)\n";
	cin >> newPopulation;
	if (newPopulation >= 0) {//offer to leave population unchanged, negitive because the population could be 0
		yearRecord.population = newPopulation * 1000000;//change the record
	}
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << fixed << setprecision(2) << setw(4) << static_cast<double>(yearRecord.population) / 1000000 << endl << endl;
	history.seekp(offSet, ios::beg);
	history.write(reinterpret_cast<char*>(&yearRecord), sizeof(Year));//put changed record into record
	
	history.seekg(offSet, ios::beg);
	history.read(reinterpret_cast<char*>(&yearRecord), sizeof(Year));

	cout << "the new record says:\n";//remind user what they input
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << fixed << setprecision(2) << setw(4) << static_cast<double>(yearRecord.population) / 1000000 << endl << endl;
	
}

/* name showPopulation
 * purpose to show the user the population for the years they chose
 * peramitures address of the fstream history
 * return void
 */
void showPopulation(fstream &history) {

	int yearFrom;// the first year to check population
	int yearTo;//the last year to check population
	long offSet;//which member of Year
	Year yearRecord;//holds data from worldhistory.dat

	cout << "What year would you like to start from?\n";
	yearFrom = valid();//where to start
	cout << "What year would you like to end at?\n";
	yearTo = valid();//where to end

	for (int i = yearFrom; i <= yearTo; i++) {

		offSet = inMemory(yearFrom);
		history.seekg(offSet, ios::beg);//go to corect area in memory
		history.read(reinterpret_cast<char*>(&yearRecord), sizeof(Year));//get record
		
		//cout << displayPopulation << " tada\n";

		cout << yearRecord.year << "    population: "<< fixed << setprecision(2) << setw(4) << static_cast<double>( yearRecord.population)/1000000 << " ";//show record
		
		int stars = yearRecord.population / 333333;

		for (int i = 0; i <= stars; i++)
			cout << "* ";
		cout << endl;

		yearFrom++;
	}

}

/* name showPopulation
 * purpose to show the user the events for the years they chose
 * peramitures address of the fstream history
 * return void
 */
void showEvent(fstream& history) {

	int yearFrom;// the first year to check population
	int yearTo;//the last year to check population
	long offSet;//which member of Year
	Year yearRecord;//holds data from worldhistory.dat

	cout << "What year would you like to start from?\n";
	yearFrom=valid();//where to start
	cout << "What year would you like to end at?\n";
	yearTo=valid();//where to end

	for (int i = yearFrom; i <= yearTo; i++) {

		offSet = inMemory(yearFrom);
		history.seekg(offSet, ios::beg);//go to corect area in memory
		history.read(reinterpret_cast<char*>(&yearRecord), sizeof(Year));//get record

		cout << yearRecord.year << ": " << yearRecord.event << endl;//show record

		yearFrom++;
	}

}