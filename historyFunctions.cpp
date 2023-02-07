#include "history.h"

// put your functions here. 

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

long inMemory(int inPutYear) {
	long offSet;
	offSet = (inPutYear - 1950) ;//the year they entered minus first posible year times the size of a year struct
	return sizeof(Year)* offSet;
}

char again() {
	
	char returnToMenu;

	cout << "Would you like to return to menu? (to use function again you must go to menu)\n";//dose the user want do anything else
	cout << "y/n       ";
	cin >> returnToMenu;
	return returnToMenu;

}

int valid() {
	bool valid;// is the user's year in the data base
	int whatYear;

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

void showYear(fstream &history) {
	int whatYear;//what year does the user want
	long offSet;//which member of Year
	
	Year yearRecord;//

	/*fstream history;
	history.open("worldHistory.dat", ios::in | ios::binary);*/

	cout << "What year would you like to know the event and population of? (1950 - 2020)\n";//tells the user the limits

	whatYear = valid();

	//go to year display population and event
	offSet = inMemory(whatYear);
	
	history.read(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << yearRecord.population << endl << endl;

}

void changeRecord(fstream &history) {
	int whatYear;//what year does the user want to modify
	long offSet;//which member of Year
	char newEvent[201];// the users new evet for the year.
	int newPopulation;// the users new population
	Year yearRecord;

	cout << "What year would you like to modify the event and population of? (1950 - 2020)\n";//tells the user the limits

	whatYear = valid();

	//go to year display population and event
	offSet = inMemory(whatYear);
	history.seekg(offSet, ios::beg); 
	history.seekp(offSet, ios::beg);

	history.read(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));//remind the user what the record curently says
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << yearRecord.population << endl << endl;
	

	cout << "what new event happened in " << yearRecord.year << "? (enter \"NOTHING NEW\" to leave unchanged)\n";
	cin >> newEvent; 
	if (newEvent =! 'NOTHING NEW') {//offer to leave event unchanged
		yearRecord.year = newEvent;//change the record
	}

	cout << "\nwhat was the new population in " << yearRecord.event << " ? (enter a negitive number to leave unchanged)\n";
	cin >> newPopulation;
	if (newPopulation <! 0) {//offer to leave population unchanged, negitive because the population could be 0
		yearRecord.population = newPopulation;//change the record
	}

	history.write(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));//put changed record into record
	history.seekg(offSet, ios::beg);
	history.read(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));

	cout << "the new record says:\n";//remind user what they input
	cout << "in " << yearRecord.year << "  " << yearRecord.event << " and the population was " << yearRecord.population << endl << endl;
	
}

void showPopulation(fstream &history) {

	int yearFrom;// the first year to check population
	int yearTo;//the last year to check population
	long offSet;
	Year yearRecord;

	cout << "What year would you like to start from?\n";
	cin >> yearFrom;//where to start
	cout << "What year would you like to end at?\n";
	cin >> yearTo;//where to end

	for (yearFrom <= yearTo, yearFrom++) {

		offSet = inMemory(yearFrom);
		history.seekg(offSet, ios::beg);//go to corect area in memory
		history.read(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));//get record
		
		cout << yearRecord.year << "    population:" << yearRecord.population << endl;//show record
	}

}

void showEvent(fstream& history) {

	int yearFrom;// the first year to check population
	int yearTo;//the last year to check population
	long offSet;
	Year yearRecord;

	cout << "What year would you like to start from?\n";
	cin >> yearFrom;//where to start
	cout << "What year would you like to end at?\n";
	cin >> yearTo;//where to end

	for (yearFrom <= yearTo, yearFrom++) {

		offSet = inMemory(yearFrom);
		history.seekg(offSet, ios::beg);//go to corect area in memory
		history.read(reinterpret_cast<char*>(&yearRecord, sizeof(Year)));//get record

		cout << yearRecord.year << "    population:" << yearRecord.event << endl;//show record
	}

}