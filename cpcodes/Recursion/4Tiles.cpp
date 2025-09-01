#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

using namespace std;
int k = 0;
void ways(int n){
    if(n<=3){
        k++;
        return;
    }
    if(n-4>=0)ways(n-4);
    ways(n-1);
}

int main(){
    int n = 8;
    ways(n);
    cout << k;
}



