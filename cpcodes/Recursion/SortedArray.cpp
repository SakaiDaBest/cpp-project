#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

using namespace std;

bool isSorted(int arr[], int n){
    if(n==0 || n==1)return true;
    if(arr[0]<arr[1] and isSorted(arr+1, n-1)){
        return true;
    }
    return false;
}

int main(){
    int arr[] = {1,2,3,4,5,6};
    int n = sizeof(arr)/sizeof(int);
    cout << isSorted(arr,n);
}



