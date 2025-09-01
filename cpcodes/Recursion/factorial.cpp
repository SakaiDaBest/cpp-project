#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

using namespace std;

int fact(int n){
    //base
    if(n==0)return 1;
    //rec
    int ans = n*fact(n-1);
    return ans;
}
int main(){
    int n;
    cin >> n;
    cout << fact(n);
}



