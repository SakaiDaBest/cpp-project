#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

using namespace std;

int fib(int n){
    if(n==0 || n==1)return n;
    int f1 = fib(n-1);
    int f2 = fib(n-2)
    return f1+f2;
}

int main(){
    int n;
    cin >> n;
    cout << fib(n);
}



