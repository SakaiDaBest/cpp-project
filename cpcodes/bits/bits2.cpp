#include <bits/stdc++.h>
#define int long long int
#define F first
#define S second
#define pb push_back

using namespace std;

//XOR of same number = 0 *** 

int countBits(int n){ //__builtin_popcount(n)
	int count = 0;
	while(n>0){
		int last_bit = (n&1);
		count+=last_bit;
		n=n>>1;
	}
	return count;
}

int convertToBinary(int n){
	int ans = 0;
	int p =1;
	while(n>0){
		int last = (n&1);
		ans += p*last;
		p*=10;
		n=n>>1;
	}
	return ans;
}


int uniqueNo2(vector<int>arr){
	int n = arr.size();
	int result = 0;
	for(int i = 0l i < arr.size();i++){
		result = result ^ arr[i];
	}
	int pos = 0;
	int temp = result;
	while((temp&1)==0){
		pos++;
		temp >>= 1;
	}

	int setA=0;
	int setB = 0;
	int mask = (1<<pos);

	for(int i = 0; i < arr.size();i++){
		if((arr[i]&mask)>0){
			setA = setB ^ arr[i];
		}else{
			setB = setB ^ arr[i];
		}
	}
	cout << setA << endl;
	cout << setB << endl;
	return;
}

//substring
void overLaynumber(char arr[], int number){
	int j = 0;
	while(number>0){
		int last_bit = number & 1;
		if(last_bit){
			cout << arr[j];
		}
		j++;
		number>>=1;
	}
	cout << endl;
}

void generateAllSubsequence(charr arr[]){
	int n = strlen(arr);
	for(int i = 0; i < (1<<n);i++){
		overLaynumber(arr,i);
	}
	return;
}

int32_t main(){
	int n = 9;
	cout << countBits(n);
	return 0;
}