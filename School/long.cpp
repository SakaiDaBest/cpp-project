#include <iostream>
using namespace std;
int main(){
    int num = 0;
    cout << "How many 'o' u want:";
    cin >> num;
    cout << "l" << string(num, 'o') << "ng";
}