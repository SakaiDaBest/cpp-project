#include <iostream>
#include <vector>
#include <limits> 
#include <string>

using namespace std;

struct List {
    string item;
};
vector<List> items;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getValidInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards invalid input
            cout << "Invalid input. Please enter a valid number: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear extra input
            return value;
        }
    }
}

int main() {
    while (true) {
        clearScreen();
        cout << "1. Add Item" << endl;
        cout << "2. Search Item" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter Choice: ";

        int choice = getValidInt();

        if (choice == 1) {
            clearScreen();
            cout << "Amount of Items: ";
            int amount = getValidInt();

            for (int i = 0; i < amount; i++) {
                List list;
                cout << "Item Name: ";
                getline(cin, list.item);
                items.push_back(list);
                cout << "You have saved " << (i + 1) << " item(s)" << endl;
            }

        } else if (choice == 2) {
            clearScreen();
            string name;
            cout << "Enter Name of Item: ";
            getline(cin, name);

            int num = 0;
            for (const auto& item : items) {
                if (item.item == name) {
                    num++;
                }
            }

            if (num >= 1) {
                cout << "Found " << num << " instance(s) of " << name << endl;
            } else {
                cout << "Item not found" << endl;
            }

            cout << "Enter anything to continue: ";
            cin.get();

        } else if (choice == 3) {
            clearScreen();
            cout << "Exiting program..." << endl;
            break;
        } else {
            cout << "Invalid Option\nEnter anything to continue: ";
            cin.get();
        }
    }

    return 0;
}
