#include <iostream>
#include <cctype>
#include <queue>
#include <string>
using namespace std;

void Menu();
void ViewAvailableFirearmsMenu();

struct Firearm {
    string id;
    string model;
    string caliber;
    int quantity;
}; // <-- semicolon added

// Initialize firearms queue
queue<Firearm> firearms;
void initializeFirearms() {
    firearms.push((Firearm){"G17A", "Glock 17", "9mm Pistol", 5});
    firearms.push((Firearm){"R870", "Remington 870", "12ga Shotgun", 3});
    firearms.push((Firearm){"AR15", "AR-15", "5.56mm Rifle", 4});
}

int main(){
    initializeFirearms();
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
    cout << "\n==========================================================" << endl;
    cout << "||           AVAILABLE FIREARMS                         ||" << endl;
    cout << "==========================================================" << endl;
    cout << "|| ID   | Model               | Caliber      | Quantity ||" << endl;
    cout << "||------|---------------------|--------------|----------||" << endl;
    queue<Firearm> temp = firearms;
    while (!temp.empty()) {
        Firearm f = temp.front();
        cout << "|| " << f.id << " | ";
        cout << f.model;
        int modelPad = 20 - f.model.length();
        for (int i = 0; i < modelPad; ++i) cout << " ";
        cout << "| " << f.caliber;
        int calPad = 12 - f.caliber.length();
        for (int i = 0; i < calPad; ++i) cout << " ";
        cout << "|    " << f.quantity << "     ||" << endl;
        temp.pop();
    }
    cout << "==========================================================" << endl;
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}