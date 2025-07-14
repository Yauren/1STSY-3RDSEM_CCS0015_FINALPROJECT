#include <iostream>
#include <string>
using namespace std;


void Menu();
void initializeFirearms();
void ViewAvailableFirearmsMenu();
void AddTransaction();
void DisplayTransactions();

struct Firearm {
    string id;
    string model;
    string caliber;
    int quantity;
};

const int MAX_FIREARMS = 10;
Firearm firearms[MAX_FIREARMS];
int front = 0, rear = -1, count = 0;


struct Transaction {
    string firearmId;
    string customerName;
    int quantityRented;
};

const int MAX_TRANSACTIONS = 20;
Transaction transactions[MAX_TRANSACTIONS];
int tFront = 0, tRear = -1, tCount = 0;


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
        case 2:
            AddTransaction();
            break;
        case 4:
            DisplayTransactions();
            break;
        case 6:
            cout << "\nExiting...";
            break;
    }

    }while (choice != 6);

    return 0;
}

void initializeFirearms() {
    firearms[++rear] = (Firearm){"G17A", "Glock 17", "9mm Pistol", 5}; count++;
    firearms[++rear] = (Firearm){"R870", "Remington 870", "12ga Shotgun", 3}; count++;
    firearms[++rear] = (Firearm){"AR15", "AR-15", "5.56mm Rifle", 4}; count++;
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
    for (int i = front; i <= rear; ++i) {
        cout << "|| " << firearms[i].id << " | ";
        cout << firearms[i].model;
        int modelPad = 20 - firearms[i].model.length();
        for (int j = 0; j < modelPad; ++j) cout << " ";
        cout << "| " << firearms[i].caliber;
        int calPad = 13 - firearms[i].caliber.length();
        for (int j = 0; j < calPad; ++j) cout << " ";
        cout << "|    " << firearms[i].quantity << "     ||" << endl;
    }
    cout << "==========================================================" << endl;
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}

void AddTransaction() {
    system("CLS");
    cout << "======================================" << endl;
    cout << "||         ADD TRANSACTION          ||" << endl;
    cout << "======================================" << endl;
    if (tCount == MAX_TRANSACTIONS) {
        cout << "||  Transaction queue is full!      ||" << endl;
        cout << "======================================" << endl;
        system("pause");
        return;
    }
    string id, customer;
    int qty;
    cout << "|| Enter Firearm ID: ";
    cin >> id;
    int idx = -1;
    for (int i = front; i <= rear; ++i) {
        if (firearms[i].id == id) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "||  Firearm not found!              ||" << endl;
        cout << "======================================" << endl;
        system("pause");
        return;
    }
    cout << "|| Enter Customer Name: ";
    cin.ignore();
    getline(cin, customer);
    cout << "|| Enter Quantity to Rent: ";
    cin >> qty;
    if (qty <= 0 || qty > firearms[idx].quantity) {
        cout << "||  Invalid quantity!               ||" << endl;
        cout << "======================================" << endl;
        system("pause");
        return;
    }
    transactions[++tRear] = {id, customer, qty};
    tCount++;
    firearms[idx].quantity -= qty;
    cout << "||  Transaction added successfully! ||" << endl;
    cout << "======================================" << endl;
    system("pause");
}

void DisplayTransactions() {
    system("CLS");
    cout << "======================================" << endl;
    cout << "||        TRANSACTION LIST          ||" << endl;
    cout << "======================================" << endl;
    if (tCount == 0) {
        cout << "||      No transactions yet.        ||" << endl;
    } else {
        cout << "|| ID    | Customer        | Qty    ||" << endl;
        cout << "||-------|-----------------|--------||" << endl;
        for (int i = tFront; i <= tRear; ++i) {
            cout << "|| " << transactions[i].firearmId;
            int idPad = 5 - transactions[i].firearmId.length();
            for (int j = 0; j < idPad; ++j) cout << " ";
            cout << " | " << transactions[i].customerName;
            int custPad = 15 - transactions[i].customerName.length();
            for (int j = 0; j < custPad; ++j) cout << " ";
            cout << " | ";
            cout.width(7);
            cout << left << transactions[i].quantityRented << "||" << endl;
        }
    }
    cout << "======================================" << endl;
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}
