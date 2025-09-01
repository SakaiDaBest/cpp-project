#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name;
    while(name.empty()){
        cout << "Enter Name: ";
        getline(std::cin, name);    //*
}
    cout << "Hello " << name << '\n';
    
    //do while loop, do some code first, then repeat if condition is true
    int number;
    /*cout << "enter a number: ";
    cin >> number;

    while(number < 0){
        cout << "enter a positive number:";
        cin >> number;
    }
    cout<< "num is " << number;*/
    do{
        cout << "Enter a positive number: ";
        cin >> number;
    }while(number < 0);
    cout << "This number is: " << number << '\n';

    //for loop
    for(int index = 1; index <= 10; index+=2){
        cout << index << '\n';
    }
    cout << "Happy New Year!\n";
    // break = break out of loop
    //continue = skip current iteration (if(i == 13){continue;})
    return 0;


}