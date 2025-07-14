#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

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

int transactionID = 1000;

struct Transaction {
    int id;
    string firearmId;
    string customerName;
    int quantityRented;
    time_t timestamp;
    bool returned;
};

const int MAX_TRANSACTIONS = 20;
Transaction transactions[MAX_TRANSACTIONS];
int tFront = 0, tRear = -1, tCount = 0;

int main(){
    initializeFirearms();
    int choice;
    do {
        Menu();
        cout << "========================================\n\n";
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
            default:
                break;
        }
    } while (choice != 6);

    return 0;
}

void initializeFirearms() {
    // G17A
    rear++;
    firearms[rear].id      = "G17A";
    firearms[rear].model   = "Glock 17";
    firearms[rear].caliber = "9mm Pistol";
    firearms[rear].quantity= 5;
    count++;

    // R870
    rear++;
    firearms[rear].id      = "R870";
    firearms[rear].model   = "Remington 870";
    firearms[rear].caliber = "12ga Shotgun";
    firearms[rear].quantity= 3;
    count++;

    // AR15
    rear++;
    firearms[rear].id      = "AR15";
    firearms[rear].model   = "AR-15";
    firearms[rear].caliber = "5.56mm Rifle";
    firearms[rear].quantity= 4;
    count++;
}

void Menu(){
    system("CLS");
    cout << "======================================\n";
    cout << "||      FIREARM RENTAL SYSTEM       ||\n";
    cout << "======================================\n";
    cout << "||  1.) View Available Firearms     ||\n";
    cout << "||  2.) Add Transaction             ||\n";
    cout << "||  3.) Update Transaction          ||\n";
    cout << "||  4.) Display Transaction List    ||\n";
    cout << "||  5.) Transaction Search          ||\n";
    cout << "||  6.) Exit                        ||\n";
    cout << "======================================\n\n";
}

void ViewAvailableFirearmsMenu() {
    system("CLS");
    cout << "\n==========================================================\n";
    cout << "||           AVAILABLE FIREARMS                         ||\n";
    cout << "==========================================================\n";
    cout << "|| ID   | Model               | Caliber      | Quantity ||\n";
    cout << "||------|---------------------|--------------|----------||\n";
    for (int i = front; i <= rear; ++i) {
        cout << "|| " << firearms[i].id << " | ";
        cout << firearms[i].model;
        int modelPad = 20 - (int)firearms[i].model.length();
        for (int j = 0; j < modelPad; ++j) cout << " ";
        cout << "| " << firearms[i].caliber;
        int calPad = 13 - (int)firearms[i].caliber.length();
        for (int j = 0; j < calPad; ++j) cout << " ";
        cout << "|    " << firearms[i].quantity << "     ||\n";
    }
    cout << "==========================================================\n";
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}

void AddTransaction() {
    system("CLS");
    cout << "======================================\n";
    cout << "||         ADD TRANSACTION          ||\n";
    cout << "======================================\n";
    if (tCount == MAX_TRANSACTIONS) {
        cout << "||  Transaction queue is full!      ||\n";
        cout << "======================================\n";
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
        cout << "||  Firearm not found!              ||\n";
        cout << "======================================\n";
        system("pause");
        return;
    }
    cout << "|| Enter Customer Name: ";
    cin.ignore();
    getline(cin, customer);
    cout << "|| Enter Quantity to Rent: ";
    cin >> qty;
    if (qty <= 0 || qty > firearms[idx].quantity) {
        cout << "||  Invalid quantity!               ||\n";
        cout << "======================================\n";
        system("pause");
        return;
    }

    tRear++;
    transactions[tRear].id             = transactionID++;
    transactions[tRear].firearmId      = id;
    transactions[tRear].customerName   = customer;
    transactions[tRear].quantityRented = qty;
    transactions[tRear].timestamp      = time(NULL);
    transactions[tRear].returned       = false;
    tCount++;

    firearms[idx].quantity -= qty;

    cout << "||  Transaction added successfully! ||\n";
    cout << "======================================\n";
    system("pause");
}

void DisplayTransactions() {
    system("CLS");
    cout << "=============================================================\n";
    cout << "||                   TRANSACTION LIST                      ||\n";
    cout << "=============================================================\n";
    if (tCount == 0) {
        cout << "||                No transactions yet.                      ||\n";
    } else {
        cout << "|| TID    | Firearm | Customer Name     | Qty |   Status   ||\n";
        cout << "||--------|---------|-------------------|-----|------------||\n";
        for (int i = tFront; i <= tRear; ++i) {
            cout << "|| ";
            cout << setw(6) << left << transactions[i].id << " | ";
            cout << setw(7) << left << transactions[i].firearmId << " | ";
            cout << setw(17) << left << transactions[i].customerName.substr(0,17) << " | ";
            cout << setw(3) << left << transactions[i].quantityRented << " | ";

            time_t now = time(NULL);
            double elapsed = difftime(now, transactions[i].timestamp);
            string status = (elapsed >= 30.0) ? "Expired" : "Ongoing";
            cout << setw(11) << left << status << "||\n";

            if (elapsed >= 30.0 && !transactions[i].returned) {
                // return back to inventory
                for (int k = front; k <= rear; ++k) {
                    if (firearms[k].id == transactions[i].firearmId) {
                        firearms[k].quantity += transactions[i].quantityRented;
                        break;
                    }
                }
                transactions[i].returned = true;
            }
        }
    }
    cout << "==============================================================\n";
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}
