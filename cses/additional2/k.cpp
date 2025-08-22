#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PairHash {
    size_t operator()(pair<ll,int> const &p) const noexcept {
        // splitmix64 on the ll part, then mix in the int
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t x = p.first + FIXED_RANDOM;
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        x = x ^ (x >> 31);
        return size_t(x ^ uint64_t(p.second));
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    // State = (current sum, next index to consider)
    using State = pair<ll,int>;
    struct Cmp { bool operator()(State const &A, State const &B) const {
        return A.first > B.first;
    }};

    priority_queue<State, vector<State>, Cmp> pq;
    unordered_set<State, PairHash> seen;
    seen.reserve(2*k);

    // Start with sum=0, idx=0 (no elements considered)
    pq.emplace(0LL, 0);
    seen.emplace(0LL, 0);

    vector<ll> ans;
    ans.reserve(k);

    while((int)ans.size() < k && !pq.empty()){
        auto cur = pq.top(); pq.pop();
        ll sum = cur.first;
        int idx = cur.second;
        ans.push_back(sum);
        if (idx < n) {
            // 1) exclude a[idx]
            State s1 = make_pair(sum, idx+1);
            if (seen.insert(s1).second) {
                pq.push(s1);
            }
            // 2) include a[idx]
            State s2 = make_pair(sum + a[idx], idx+1);
            if (seen.insert(s2).second) {
                pq.push(s2);
            }
        }
    }

    // print the k smallest sums
    for(int i = 0; i < (int)ans.size(); i++){
        cout << ans[i] << (i+1<k?' ':'\n');
    }
    return 0;
}
