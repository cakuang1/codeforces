#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
 
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> freq;
 
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        freq[a[i]]++;
    }
 
    long long result = 1;
    for (auto &[val, f] : freq) {
        result = (result * (f + 1)) % MOD;
    }
 
    // Exclude empty subsequence
    result = (result - 1 + MOD) % MOD;
 
    cout << result << endl;
    return 0;
}



// wdetmeir w