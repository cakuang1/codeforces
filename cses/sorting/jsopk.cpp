#include <bits/stdc++.h>
using namespace std;

// Fenwick / BIT supporting point‐updates and prefix sums.
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1,0) {}
    // add v at position i
    void add(int i, int v=1) {
        for(; i<=n; i+=i&-i) f[i] += v;
    }
    // sum of [1..i]
    int sum(int i) const {
        int s = 0;
        for(; i>0; i-=i&-i) s += f[i];
        return s;
    }
    // find smallest i such that sum(i) >= target (1-indexed search)
    int findByOrder(int target) const {
        int i = 0;
        int bit = 1 << (31 - __builtin_clz(n)); 
        for(; bit; bit >>= 1) {
            int nxt = i + bit;
            if(nxt <= n && f[nxt] < target) {
                target -= f[nxt];
                i = nxt;
            }
        }
        return i + 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    Fenwick fenw(n);
    // initially all alive
    for(int i = 1; i <= n; i++) 
        fenw.add(i, 1);

    long long cur = 0;  // 0-index into the circle of remaining children
    int rem = n;

    vector<int> answer;
    answer.reserve(n);

    while(rem--){
        cur = (cur + k) % (rem + 1);
        // we want the (cur+1)-th alive child
        int idx = fenw.findByOrder(cur + 1);
        answer.push_back(idx);
        fenw.add(idx, -1);  // remove child idx
    }

    // output the elimination order
    for(int x : answer) 
        cout << x << ' ';
    cout << '\n';
    return 0;
}
