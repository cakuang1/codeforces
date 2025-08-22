#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // min‑heap of (value, original_index)
    // greater<> gives us a min‑heap behavior
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    vector<int> ans;
    ans.reserve(n);

    // 'next_j' is the next array index we haven't pushed yet
    int next_j = 0;
    // initially push all j in [0 .. min(n-1, k)]
    int limit = (k < n-1 ? int(k) : n-1);
    while(next_j <= limit) {
        pq.emplace(a[next_j], next_j);
        ++next_j;
    }

    // Build the result from i=0..n-1
    for(int i = 0; i < n; i++){
        // Pop the smallest eligible element
        auto [val, j] = pq.top(); 
        pq.pop();
        ans.push_back(val);

        // Now the window of eligibility slides forward:
        // we can now include index (i+k+1), if it's < n
        long long new_limit = i + k + 1;
        if (new_limit < n) {
            pq.emplace(a[int(new_limit)], int(new_limit));
        }
    }

    // Print
    for(int i = 0; i < n; i++){
        cout << ans[i] << (i+1<n ? ' ' : '\n');
    } 
    
        
    return 0;
}

// doesti wreally erwor kwew?  er w
