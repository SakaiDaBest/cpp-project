#include <bits/stdc++.h>
using namespace std;

int main(){
    ofstream oi("Items.txt", ios::out);
    string itemSold[3] ={"banana", "chicken", "apple"};
    for(auto& i : itemSold){
        oi << i;
        oi << endl;
    } 
}