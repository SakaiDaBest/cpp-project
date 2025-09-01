#include <bits/stdc++.h>
using namespace std;

int main(){
    string chicken;
    cout << "Enter a string: ";
    cin >> chicken;

    for (int i = 0; i < chicken.length() - 1; i++) {
        if (chicken[i] > chicken[i+1]) {
            cout << "no";
            return 0; 
        }
    }
    cout << "yes";
    return 0;
}