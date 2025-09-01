#include <bits/stdc++.h>
#define int long long int
#define F first
#define S second
#define pb push_back

using namespace std;

int countBits(int n){
	int count = 0;
	while(n>0){
		int last_bit = (n&1);
		count+=last_bit;
		n=n>>1;
	}
	return count;
}

int32_t main(){
	int n = 9;
	cout << countBits(n);
	return 0;
}