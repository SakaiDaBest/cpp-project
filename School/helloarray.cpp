#include <bits/stdc++.h>
using namespace std;
double getTotal(double price[], int size);
int main(){
    string car[] = {"Proton Saga", "Myvi", "Your Mom"}; //array
    cout << car[0].at(4) << '\n';
    /*sizeof() shows how large the file is
     (can be used to find how many shit is in an array)*/
    double gpa = 2.5;
    cout << sizeof(gpa) << " bytes\n";
    for(string card : car) {
        cout << card << '\n';
    }
    double price[] = {1.1, 2.2, 3.07, 4.11};
    int size = sizeof(price)/sizeof(price[0]);
    double total = getTotal(price, size);

    cout << "$" << total;
    const int SIZE = 50;
    string chick[100];
    string lusts[SIZE];
    fill(chick, chick + 100, "chicken");
    fill(lusts, lusts(SIZE/2), "pron");
    fill(lusts + (SIZE/2), lusts + SIZE, "horny");
    
    for(string n : chick){
        cout << n << '\n';
    }

    for(string l : lusts){
        cout << l << '\n';
    }
    return 0;

}

double getTotal(double price[], int size){
    double total = 0;
    for(int i = 0; i < size; i++){
        total += price[i];
        
    }
    return total;
}

