#include <iostream>
#include <ctime>
#include <string>
#include <istream>
using namespace std;

void BIRTHDAY();

int main() {
    srand(time(NULL));
    int num = (rand() % 6) + 1;
    cout << num << '\n';
    srand(time(0));
    int randomnum = rand() % 6 + 1;
    BIRTHDAY();
    /*switch(randomnum){
       used to make GACHA 
    }*/
}

void BIRTHDAY(){
    string name;
    cout << "Name?\n";
    getline(cin, name);
    cout << "Happy Birthday to " << name << "!\n";
}
