#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <ctime>
using namespace std;

// ----- STRUCTS -----
struct Transaction {
    int transactionID;
    string customerName;
    string firearmID;
    string firearmModel;
    string rentalDate;
    string status; // "Pending", "Returned", "Expired"
};

struct Firearm {
    string firearmID;
    string model;
    int totalQuantity;
    int availableCount;
};

// ----- GLOBAL INVENTORY (Hardcoded) -----
const int MAX_FIREARMS = 3;
Firearm firearms[MAX_FIREARMS] = {
    {"1001", "Glock 17", 5, 5},
    {"1002", "M4 Carbine", 3, 3},
    {"1003", "Remington 870", 4, 4}
};

// ----- FUNCTION PROTOTYPES -----
void loadTransactions(queue<Transaction>&);
void saveTransactions(queue<Transaction>);
void addTransaction(queue<Transaction>&);
void displayMenu();
string getCurrentDate();
void updateInventory(string firearmID, int change);
Firearm* findFirearmByID(string id);
int generateTransactionID();

// ----- MAIN -----
int main() {
    queue<Transaction> transactionQueue;
    loadTransactions(transactionQueue);

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addTransaction(transactionQueue); break;
            case 5: saveTransactions(transactionQueue); break;
            default: cout << "Function not implemented yet.\n";
        }
    } while (choice != 5);

    return 0;
}

// ----- MENU DISPLAY -----
void displayMenu() {
    cout << "\nFirearm Rental System\n";
    cout << "1. Add Transaction\n";
    cout << "2. Update Transaction\n";
    cout << "3. Find Transaction\n";
    cout << "4. View Transaction List\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

// ----- CURRENT DATE HELPER -----
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

// ----- LOAD TRANSACTIONS FROM FILE -----
void loadTransactions(queue<Transaction> &q) {
    ifstream inFile("transactions.txt");
    Transaction t;
    while (inFile >> t.transactionID) {
        inFile.ignore();
        getline(inFile, t.customerName, ',');
        getline(inFile, t.firearmID, ',');
        getline(inFile, t.firearmModel, ',');
        getline(inFile, t.rentalDate, ',');
        getline(inFile, t.status);
        q.push(t);
    }
    inFile.close();
}

// ----- SAVE TRANSACTIONS TO FILE -----
void saveTransactions(queue<Transaction> q) {
    ofstream outFile("transactions.txt");
    while (!q.empty()) {
        Transaction t = q.front(); q.pop();
        outFile << t.transactionID << ","
                << t.customerName << ","
                << t.firearmID << ","
                << t.firearmModel << ","
                << t.rentalDate << ","
                << t.status << endl;
    }
    outFile.close();
    cout << "Transactions saved.\n";
}

// ----- FIND FIREARM BY ID -----
Firearm* findFirearmByID(string id) {
    for (int i = 0; i < MAX_FIREARMS; i++) {
        if (firearms[i].firearmID == id)
            return &firearms[i];
    }
    return nullptr;
}

// ----- UPDATE INVENTORY -----
void updateInventory(string firearmID, int change) {
    Firearm* f = findFirearmByID(firearmID);
    if (f != nullptr) {
        f->availableCount += change;
    }
}

// ----- GENERATE TRANSACTION ID -----
int generateTransactionID() {
    static int lastID = 1000;
    return ++lastID;
}

// ----- ADD TRANSACTION -----
void addTransaction(queue<Transaction> &q) {
    string name, firearmID;
    cout << "Enter customer name: ";
    getline(cin, name);
    cout << "Enter firearm ID: ";
    getline(cin, firearmID);

    Firearm* f = findFirearmByID(firearmID);
    if (f == nullptr) {
        cout << "Invalid firearm ID.\n";
        return;
    }
    if (f->availableCount <= 0) {
        cout << "No available units for this firearm.\n";
        return;
    }

    Transaction t;
    t.transactionID = generateTransactionID();
    t.customerName = name;
    t.firearmID = firearmID;
    t.firearmModel = f->model;
    t.rentalDate = getCurrentDate();
    t.status = "Pending";

    updateInventory(firearmID, -1);
    q.push(t);

    cout << "Transaction added.\n";
}
