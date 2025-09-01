#include <bits/stdc++.h>
#define int long
#define F first
#define S second
#define pb push_back
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

using namespace std;

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
    const char* comma = strchr (names + 1, ',');
    cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

const int INF = 1e9;
 
void solve(){
    int n, k;
    long long x;
    cin >> n >> k >> x;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    int N = n * k;
    vector<int> b(N);
    for (int i = 0; i < N; i++){
        b[i] = a[i % n];
    }
    
    vector<int> prefix(N + 1, 0);
    for (int i = 1; i <= N; i++){
        prefix[i] = prefix[i - 1] + b[i - 1];
    }
    

    int ans = 0;
    int r = 0;
    for (int l = 0; l < N; l++){
        if(r < l) r = l;
        while(r < N && prefix[r + 1] - prefix[l] < x){
            r++;
        }
        if(r < N && prefix[r + 1] - prefix[l] >= x)
            ans++;
    }
    
    cout << ans << "\n";
}


int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    clock_t z = clock();

    int t;
    cin >> t;
    while (t--) solve();

    cerr << "Run Time : " << ((double)(clock() - z) / CLOCKS_PER_SEC);
    set<int>s;
    
    return 0;
}



