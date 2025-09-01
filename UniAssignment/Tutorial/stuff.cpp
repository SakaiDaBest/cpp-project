#include <iostream>
#include <string>
#include <iomanip>
#define d double
using namespace std;
int main() {
	string name;
	int days,category;
	cout << "Enter name, days: ";
	cin >> name >> days ;
    cout << "Category" << setw(30) << "Description" << setw(30) << "Price per Day"<<endl;
    cout << "0" << setw(30) << "Economy" << setw(30) << "RM25"<<endl;
	cout << "1" << setw(30) << "Standard" << setw(30) << "RM40"<<endl;
	cout << "2" << setw(30) << "Premium" << setw(30) << "RM60"<<endl;
	cout << "3" << setw(30) << "Luxury" << setw(30) << "RM100"<<endl;
	cout << "Enter Your Category: ";
	cin >> category;
    while(!(category>=0 && category < 4)){
        cout << "ERROR\nPlease Insert a valid category: ";
        cin >> category; 
    }
	d total_cost;
	int price;
    switch(category){
        case 1: price=25;
        case 2: price = 40;
        case 3: price = 60;
        case 4: price = 100;
    }
	total_cost = days*price;
	cout << "\nCustomer Name is " << name << endl;
	cout << "Days rented is " << days << endl;
	cout << "Total cost is RM" << total_cost;
}