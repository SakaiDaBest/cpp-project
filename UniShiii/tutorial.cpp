#include <iostream>
#include <string>
#include <cctype> 

using namespace std;

int main() {
    string num = "1234";
    int ans = 0;
    for(int i = 0; i < num.length();i++){
        char a = num[i];
        ans += atoi(&a);
    }
    cout << ans;
}