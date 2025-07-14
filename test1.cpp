#include <iostream>
#include <cctype>
using namespace std;

void Menu();
void ViewAvailableFirearmsMenu();

int main(){
	int choice;
    char confirmation;
    do{
        Menu();
        cout << "========================================" << "\n\n";
        cout << "Select an option: ";
        cin >> choice;

          switch (choice) {
            case 1:
                ViewAvailableFirearmsMenu();
                break;
    
            case 6:
                cout << "\nExiting...";
                break;
        }

    }while (choice != 6);


	return 0;
}

void Menu(){
    system("CLS");
	cout << "======================================" << endl;
	cout << "||                                  ||" << endl;
	cout << "||      FIREARM RENTAL SYSTEM       ||" << endl;
	cout << "||                                  ||" << endl;
	cout << "======================================" << endl;
	cout << "||                                  ||" << endl;
	cout << "||  1.) View Available Firearms     ||" << endl;
	cout << "||  2.) Add Transaction             ||" << endl;
	cout << "||  3.) Update Transaction          ||" << endl;
	cout << "||  4.) Display Transaction List    ||" << endl;
	cout << "||  5.) Transaction Search          ||" << endl;
	cout << "||  6.) Exit                        ||" << endl;
	cout << "||                                  ||" << endl;
	cout << "======================================" << "\n\n";
	
}

void ViewAvailableFirearmsMenu() {
    system("CLS");
    cout << "\n===============================================" << endl;
    cout << "||           AVAILABLE FIREARMS              ||" << endl;
    cout << "===============================================" << endl;
    cout << "|| ID   | Model               | Caliber      ||" << endl;
    cout << "||------|---------------------|--------------||" << endl;
    cout << "|| G17A | Glock 17            | 9mm Pistol   ||" << endl;
    cout << "|| R870 | Remington 870       | 12ga Shotgun ||" << endl;
    cout << "|| AR15 | AR-15               | 5.56mm Rifle ||" << endl;
    cout << "===============================================" << endl;
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}