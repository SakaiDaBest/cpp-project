#include <iostream>
using namespace std;
int main() {
    int DAY;
    cout << "WHAT DAY IS IT BITCH:";
    cin >> DAY;

    switch(DAY) {
        case 1:
            cout << "IT IS MONDAY" << '\n';
            break;
        case 2:
            cout << "IT IS TUESDAY" << '\n';
            break;
        case 3:
            cout << "IT IS WEDNESDAY" << '\n';
            break;
        case 4:
            cout << "IT IS THURSDAY" << '\n';
            break;
        case 5:
            cout << "IT IS FRIDAY" << '\n';
            break;
        case 6:
            cout << "IT IS SATURDAY" << '\n';
            break;
        case 7:
            cout << "IT IS SUNDAY" << '\n';
            break;
        default:
            cout << "ERROR" << '\n';
            break;
    }

    int grade = 55;
    /*if(grade >= 60)
    {
        cout << "you passed WOOHOO!" << '\n';
    }
    else{
        cout << "you failed BOOHOO!" << '\n';
    }
    return 0;*/

    // condition ? expression1 : expression2
    //if true it picks the first false pick second
    (grade >= 60) ? cout << "you passed WOOHOO!" : cout << "YOU FAILED!";

    // && 2 conditions are true, || at least 1 is true, ! true become false vice versa (use in if statement)
    //x.length() = len name.empty(), check if something is empty, clear(), remove the variable, append(x) add something to a word
    //::getline(), allows multiple line of strings in input
    //.at() letter at x number location, insert.(position, word), x.find(' ')
    //name.erase(x, y)from where to where
    
}