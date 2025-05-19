#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Function to compute least common multiple (lcm) of two numbers.
ll lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

// BFS that computes minimal number of operations to transform X to Y (X >= Y)
// using the allowed operations: subtract 1, or for any x in [2,k], subtract (cur mod x) (if nonzero).
// We assume that the difference X - Y is at most L (so the state space is small).
int bfsInterval(ll X, ll Y, int k) {
    // We will map each number in [Y, X] to an index 0 ... (X - Y)
    int len = X - Y + 1;
    vector<int> dist(len, -1);
    auto idx = [&](ll x) { return (int)(x - Y); };
    queue<ll> qu;
    qu.push(X);
    dist[idx(X)] = 0;
    while(!qu.empty()){
        ll cur = qu.front();
        qu.pop();
        if(cur == Y) return dist[idx(cur)];
        int d = dist[idx(cur)];
        // Operation 1: subtract 1.
        if(cur - 1 >= Y && dist[idx(cur-1)] == -1) {
            dist[idx(cur-1)] = d + 1;
            qu.push(cur - 1);
        }
        // Operation 2: for each x in [2, k], subtract (cur mod x) if nonzero.
        for (int x = 2; x <= k; x++){
            ll rem = cur % x;
            if(rem != 0) {
                ll nxt = cur - rem;
                if(nxt >= Y && dist[idx(nxt)] == -1) {
                    dist[idx(nxt)] = d + 1;
                    qu.push(nxt);
                }
            }
        }
    }
    return -1; // unreachable (should not happen)
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll A, B; int k;
    cin >> A >> B >> k; // Note: 1 ≤ B ≤ A ≤ 1e18, 2 ≤ k ≤ 15.
    
    // Compute L = lcm(2,3,...,k)
    ll L = 2;
    for (int i = 3; i <= k; i++){
        L = lcm(L, i);
    }
    // We'll work with the interval [B, A]. (We want to reduce A to B.)
    
    // If the whole interval length is less than L, we can solve it with one BFS.
    if(A - B < L){
        cout << bfsInterval(A, B, k) << "\n";
        return 0;
    }
    
    // Otherwise, note that any optimal transformation must include all numbers in [B, A] that are divisible by L.
    // Let topAnchor = the largest number <= A divisible by L.
    // Let botAnchor = the smallest number >= B divisible by L.
    ll topAnchor = (A / L) * L; // floor division.
    ll botAnchor = ((B + L - 1) / L) * L; // ceiling division.
    
    // If no anchor exists, then the whole interval is less than L.
    if(topAnchor < botAnchor) {
        cout << bfsInterval(A, B, k) << "\n";
        return 0;
    }
    
    // Count how many anchor numbers (multiples of L) lie in [B, A].
    ll mAnchors = ((topAnchor - botAnchor) / L) + 1;
    
    // Compute cost for top interval: from A down to topAnchor.
    int topCost = 0;
    if(A != topAnchor) {
        topCost = bfsInterval(A, topAnchor, k);
    }
    // Compute cost for bottom interval: from botAnchor down to B.
    int botCost = 0;
    if(B != botAnchor) {
        botCost = bfsInterval(botAnchor, B, k);
    }
    // Compute cost for a full interval of length L: from some number X (divisible by L) down to X - L.
    int fullCost = bfsInterval(topAnchor, topAnchor - L, k);
    
    // Total answer:
    ll ans = topCost + botCost + (mAnchors - 1) * (ll)fullCost;
    
    cout << ans << "\n";
    return 0;
}


// lcm w