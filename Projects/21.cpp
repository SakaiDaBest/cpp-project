#include <bits/stdc++.h>
using namespace std;

class AI {
protected:
    vector<int> cards;

public:
    AI() { 
        cards.push_back(rand() % 9 + 1); 
    }

    int cardSum() {
        int sum = 0; // Fix: Initialize sum
        for (auto i : cards) {
            sum += i;
        }
        return sum;
    }

    int get() {
        while (cardSum() <= 16) { // AI stops drawing if sum > 16
            cards.push_back(rand() % 9 + 1);
        }
        return cardSum();
    }

    void AIShow() {
        for (auto i : cards) {
            cout << "  " << i << "  ";
        }
        cout << endl;
    }
};

class Player {
protected:
    vector<int> cards;

public:
    Player() {
        cards.push_back(rand() % 9 + 1);
    }

    void GetCards() {
        cards.push_back(rand() % 9 + 1);
    }

    void ShowCards() {
        for (auto i : cards) {
            cout << "  " << i << "  ";
        }
        cout << endl;
    }

    int CardSum() {
        int sum = 0; // Fix: Initialize sum
        for (auto i : cards) {
            sum += i;
        }
        return sum;
    }
};

void systemclear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getValidInt() {
    int value;
    while (true) {
        cout << "Enter a number: ";
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input, Try Again." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    srand(time(0)); // Fix: Seed the random generator
    int money = 100;
    while (true) {
        systemclear();
        cout << "Your Wallet: $" << money << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Exit Game" << endl;
        cout << "Choice: ";
        int choice = getValidInt();

        if (choice == 2) break;

        if (choice != 1) {
            cout << "Invalid Input, Press Enter to Continue";
            cin.ignore();
            continue;
        }

        bool result = true;

        while (result) {
            systemclear();
            Player me;
            AI ai;
            me.GetCards();
            cout << "Your Wallet: $" << money << endl;
            cout << "How much money would you like to bet?" << endl;
            int qmoney = getValidInt();
            if(qmoney>money||qmoney<0){
                cout << "Invalid Amount of Money.";
                cin.ignore();
                break;
            }
            money -=qmoney;
            while (true) {
                systemclear();
                cout << "Your Hand: ";
                me.ShowCards();
                cout << "1. Hit" << endl;
                cout << "2. Fold" << endl;

                int choice2 = getValidInt();
                if (choice2 == 1) {
                    systemclear();
                    me.GetCards();
                    int sum = me.CardSum();
                    if (sum > 21) {
                        cout << "Bust. You Lose!" << endl;
                        cin.ignore();
                        result = false;
                        break;
                    }
                } else if (choice2 == 2) {
                    systemclear();
                    int AIsum = ai.get();
                    int mesum = me.CardSum();

                    cout << "Your Hand: ";
                    me.ShowCards();
                    cout << "Dealer's Hand: ";
                    ai.AIShow();

                    if (AIsum > 21 || mesum > AIsum) {
                        cout << "You Win!" << endl;
                        money+= qmoney*2;
                    } else if (AIsum > mesum) {
                        cout << "You Lose!" << endl;
                    } else {
                        cout << "Draw!" << endl;
                        money += qmoney;
                    }
                    cin.ignore();
                    result = false;
                    break;
                }
            }
        }
    }

    return 0;
}
