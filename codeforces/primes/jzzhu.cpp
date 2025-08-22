#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 1) Build divp[i] = largest prime divisor of i (for i>=2)
    vector<int> divp(N+1, 0);
    for (int i = 2; i <= N; i++) {
        if (divp[i] == 0) {
            // i is prime
            for (int j = i; j <= N; j += i) {
                divp[j] = i;  // overwrite; in the end it'll be the largest prime divisor
            }
        }
    }

    // 2) Bucket all *odd* numbers by their largest prime divisor
    vector<vector<int>> E(N+1);
    for (int i = 3; i <= N; i += 2) {
        E[ divp[i] ].push_back(i);
    }

    vector<pair<int,int>> V;
    vector<bool> used_special(N+1,false);

    // 3) For each prime p >= 3, pair within E[p]
    for (int p = 3; p*2 <= N; p++) {
        auto &vec = E[p];
        int sz = vec.size();
        if (sz == 0) continue;

        // Pair off from the back (largest odds first)
        for (int j = 0; j+1 < sz; j += 2) {
            int u = vec[sz - j - 1];
            int v = vec[sz - j - 2];
            V.emplace_back(u, v);
        }

        // If odd count, peel off the "special" 2*p
        if (sz % 2 == 1 && 2*p <= N) {
            V.emplace_back(p, 2*p);
            used_special[2*p] = true;
        }
    }
    // 4) Finally, collect all remaining unused *evens* and pair them
    vector<int> evens;
    for (int x = 2; x <= N; x += 2) {
        if (!used_special[x]) {
            evens.push_back(x);
        }
    }
    for (int i = 0; i+1 < (int)evens.size(); i += 2) {
        V.emplace_back(evens[i], evens[i+1]);
    }

    // 5) Output result
    cout << V.size() << "\n";
    for (auto &pr : V) {
        cout << pr.first << " " << pr.second << "\n";
    }
    return 0;
}
 
// buildign wedetmeirn enign wewhich werdivosr  w
// wnubmer of weidvosrwer