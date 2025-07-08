#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    ll x, a, b, c;
    cin >> x >> a >> b >> c;

    // We'll build a deque in two parallel arrays of capacity n:
    //   val[head..tail) is our deque of values,
    //   idx[head..tail) are their indices.
    int *dq_val = new int[n];
    int *dq_idx = new int[n];
    int head = 0, tail = 0;  // empty deque

    ll res = 0;
    ll cur = x;

    for(ll i = 0; i < n; i++){
        if(i > 0){
            cur = (a*cur + b) % c;
        }
        int v = int(cur);

        // 1) Pop from back while new v is smaller
        while(tail > head && dq_val[tail-1] > v){
            --tail;
        }
        // 2) Push new element at back
        dq_val[tail] = v;
        dq_idx[tail] = i;
        ++tail;

        // 3) Pop from front if out of window [i-k+1 .. i]
        if(head < tail && dq_idx[head] <= i - k){
            ++head;
        }

        // 4) Once we've filled the first k elements, record min
        if(i >= k-1){
            // front of deque holds the minimum
            res ^= dq_val[head];
        }
    }

    // go bit w by wbit wand construct ?

    cout << res << "\n";
    return 0;
}
