#include <bits/stdc++.h>
using namespace std;


int main() {

	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read all input at once
    string input, line;
    while (getline(cin, line)) {
        input += line + "\n";
    }

    // Redirect input stream for processing
    stringstream ss(input);
    cin.rdbuf(ss.rdbuf());
	
	int n;
	cin >>n;
	vector<int>nums(n);
	for(auto& i : nums){
		cin >> i;
	}
	sort(nums.begin(),nums.end());
	for(int i = 2;i < n;i++){
		if(nums[i-2]+nums[i-1]>nums[i]){
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
}
