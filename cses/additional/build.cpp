#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int m = n*(n-1)/2;
    vector<ll> s(m);
    for(int i = 0; i < m; i++){
        cin >> s[i];
    }
    sort(s.begin(), s.end());

    // Original multiset of sums
    map<ll,int> cnt;
    for(ll x : s) cnt[x]++;

    // s[0] = A1+A2, s[1] = A1+A3
    ll S12 = s[0], S13 = s[1];

    vector<ll> A(n);
    auto try_k = [&](int k) -> bool {
        ll S23 = s[k];
        // Solve for A1, A2, A3
        ll sum = S12 + S13 - S23;
        if (sum & 1) return false;           // must be even
        ll A1 = sum/2;
        ll A2 = S12 - A1;
        ll A3 = S13 - A1;
        if (A1 <= 0 || A2 <= 0 || A3 <= 0) return false;

        // local copy of the multiset
        auto M = cnt;
        auto remove = [&](ll x){
            auto it = M.find(x);
            if (it == M.end()) return false;
            if (--it->second == 0) M.erase(it);
            return true;
        };

        // initialize A[0..2]
        A[0] = A1; A[1] = A2; A[2] = A3;
        // remove their pair‐sums
        if (!remove(A1+A2)) return false;
        if (!remove(A1+A3)) return false;
        if (!remove(A2+A3)) return false;

        // build the rest
        for(int i = 3; i < n; i++){
            // the smallest remaining sum must be A1 + A[i]
            if (M.empty()) return false;
            ll smin = M.begin()->first;
            ll Ai = smin - A1;
            if (Ai <= 0) return false;
            A[i] = Ai;
            // remove sums A[i] + A[j] for j < i
            for(int j = 0; j < i; j++){
                if (!remove(A[i] + A[j])) return false;
            }
        }
        
         
        return true;
    };

    // try candidates for s[2], s[3], ... until one works
    for(int k = 2; k < m; k++){
        if (try_k(k)) {
            for(int i = 0; i < n; i++){
                cout << A[i] << (i+1<n?' ':'\n');
            }
            return 0;
        }
    }

    // we are guaranteed a solution exists, so we should never reach here
    return 0;
}
