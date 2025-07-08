#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    // freq[x] = count of x in current window, for x in [0..k]
    vector<int> freq(k+1, 0);
    // set of all values in [0..k] that currently have freq==0
    set<int> missing;
    for(int x = 0; x <= k; x++){
        missing.insert(x);
    }

    // initialize first window [0..k-1]
    for(int i = 0; i < k; i++){
        int x = arr[i];
        if(x <= k){
            if(freq[x] == 0) {
                missing.erase(x);
            }
            freq[x]++;
        }
    }

    // answer for each window
    vector<int> ans;
    ans.reserve(n - k + 1);
    ans.push_back(*missing.begin());

    // slide
    for(int i = k; i < n; i++){
        int out = arr[i - k];
        if(out <= k){
            freq[out]--;
            if(freq[out] == 0){
                missing.insert(out);
            }
        }
        int in = arr[i];
        if(in <= k){
            if(freq[in] == 0){
                missing.erase(in);
            }
            freq[in]++;
        }
        ans.push_back(*missing.begin());
    }

    // output
    for(int i = 0; i < (int)ans.size(); i++){
        cout << ans[i] << (i+1 < (int)ans.size() ? ' ' : '\n');
    }
    return 0;
}
