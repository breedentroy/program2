#include "history.h"

int main() {

	char choice;
	char returnToMenu;
	fstream history;

	history.open("worldHistory.dat", ios::in | ios::out | ios::binary);

	cout << "Welcome to the history of the world\n";//tell the user were they are at 

	do {
		choice = menu();

		if (choice == '1') {
			showYear(history);
			returnToMenu = again();
		}
		else if (choice == '2') {
			showPopulation(history);
			returnToMenu = again();
		}
		else if (choice == '3') {// this is kind of the oppisite of showYear
			changeRecord(history);
			returnToMenu = again();
		}
		else if (choice == '4') {
			showEvent(history);
			returnToMenu = again();
		}
		else {
			returnToMenu = 'n';
		}
	} while (returnToMenu == 'y' || returnToMenu == 'Y');

	history.close();

	return 0; 
}