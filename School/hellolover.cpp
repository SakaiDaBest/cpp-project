#include <iostream>

using namespace std;
//functions cannot see variables made in other functions, if :: in front of variable, will use global instead of normal
void bakePizza();
void bakePizza(string topping1);
int main(){

    bakePizza("Pepperoni");

    return 0;
}

void bakePizza(){
    cout << "Here is your Pizza.\n";
}
void bakePizza(string topping1){
    cout << "Here is your " << topping1 << " pizza\n";
}