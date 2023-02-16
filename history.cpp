#include "history.h"
/**********************************************
 *  Name: Troy Breeden
 *  File Name: history.cpp
 *  Description: holds main
 **********************************************/


/* name main
 * purpose to show the user the population and/or events for the years they chose or modify the worldHistory.dat file
 * peramitures none
 * return int 0
 */
int main() {

	char choice;//what does the user want to do
	char returnToMenu;//begin again
	fstream history;//access to worldHistory.dat

	history.open("worldHistory.dat", ios::in | ios::out | ios::binary);

	cout << "Welcome to the history of the world\n";//tell the user were they are at 

	do {
		choice = menu();

		if (choice == '1') {
			showYear(history);//shows the user the event and poulation of their selected year
			returnToMenu = again();
		}
		else if (choice == '2') {
			showPopulation(history);//shows the population for all the years between what they select
			returnToMenu = again();
		}
		else if (choice == '3') {// this is kind of the oppisite of showYear
			changeRecord(history);// allows user to change the record for a selected year
			returnToMenu = again();
		}
		else if (choice == '4') {
			showEvent(history);//shows the events for all the years between what they select
			returnToMenu = again();
		}
		else {
			returnToMenu = 'n';
		}
	} while (returnToMenu == 'y' || returnToMenu == 'Y');

	history.close();

	return 0; 
}