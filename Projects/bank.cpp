#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

class Banking{
    unordered_map<int,int> accountBalances;
    static int nextAccountID;
public:
    int createAccount(){
        int accountID = nextAccountID++;
        accountBalances[accountID]=0;
        cout << "New Account Created. Account ID: "<<accountID <<endl;
        return accountID;
    }

    void deposit(int accountID){
        if (accountBalances.find(accountID) == accountBalances.end()) {
            cout << "Account not found!" << endl;
            return;
        }

        int dep;
        cout << "Enter deposit amount: ";
        while(true){
            cin >> dep;
            if (dep > 0) break;
            cout << "Invalid amount! Try again: ";
        }
        accountBalances[accountID]+=dep;
        cout << "Deposited " << dep << ". New balance: " << accountBalances[accountID] << endl;

    }
    void withdraw(int accountID){
        if (accountBalances.find(accountID) == accountBalances.end()) {
            cout << "Account not found!" << endl;
            return;
        }

        int wit;
        cout << "Enter withdrawal amount";
        while(true){
            if(wit>0 && wit <= accountBalances[accountID])break;
            cout << "Invalid" << endl;
        }
        accountBalances[accountID] -= wit;
        cout << "Withdrawn " << wit << ". New balance: " << accountBalances[accountID] << endl;
 
    }
    void showBalances() {
        if (accountBalances.empty()) {
            cout << "No accounts exist in this bank." << endl;
            return;
        }

        cout << "\nAccount Balances:" << endl;
        for (auto &pair : accountBalances) {
            cout << "Account " << pair.first << ": $" << pair.second << endl;
        }
    }
};

int Banking::nextAccountID = 1;


int main() {
    BankSystem system;
    system.run();
    return 0;
}