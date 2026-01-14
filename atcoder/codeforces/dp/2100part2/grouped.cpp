#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Segment {
    int L, R;   // [L, R] is the range of destination carriages
    ll supply;  // number of passengers from this carriage
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<ll> A(N+1);
    for (int i = 1; i <= N; i++){
        cin >> A[i];
    }
    vector<int> D(N+1);
    for (int i = 1; i <= N; i++){
        cin >> D[i];
    }
    
    // Build segments: for each carriage i, passengers can go to any destination in:
    // [ max(1, i-D[i]), min(N, i+D[i]) ]
    vector<Segment> segs;
    segs.reserve(N);
    for (int i = 1; i <= N; i++){
        int L = max(1, i - D[i]);
        int R = min(N, i + D[i]);
        segs.push_back({L, R, A[i]});
    }
    
    // Sort segments by their left endpoint.
    sort(segs.begin(), segs.end(), [](const Segment &a, const Segment &b) {
        return a.L < b.L;
    });
    
    // Total supply (for setting an upper bound).
    ll totalSupply = 0;
    for (int i = 1; i <= N; i++){
        totalSupply += A[i];
    }
    
    // Lower bound: at least the average load (rounded up)
    ll lo = (totalSupply + N - 1) / N;
    // Upper bound: worst-case, one carriage takes all passengers.
    ll hi = totalSupply;
    ll ans = hi;
    
    // Given a candidate Z (maximum passengers per carriage), check if a valid assignment exists.
    auto canDo = [&](ll Z) -> bool {
        // We will simulate filling destination carriages from 1 to N.
        // Each destination carriage j can take at most Z passengers.
        // We use a priority queue to store available segments (i.e., initial carriages)
        // that can donate to the current destination. We order segments by their right endpoint.
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        // Make a copy of the supply available from each segment.
        vector<ll> rem(segs.size());
        for (size_t i = 0; i < segs.size(); i++){
            rem[i] = segs[i].supply;
        }
        
        int segIndex = 0;
        // Iterate over destination carriages 1...N.
        for (int dest = 1; dest <= N; dest++){
            // Add all segments that start at or before dest.
            while (segIndex < segs.size() && segs[segIndex].L <= dest) {
                pq.push({segs[segIndex].R, segIndex});
                segIndex++;
            }
            // Carriage dest has capacity Z.
            ll capacity = Z;
            // Fill carriage dest using available segments.
            while (capacity > 0 && !pq.empty()){
                auto [R, idx] = pq.top();
                pq.pop();
                // If the segment cannot reach dest, then its supply cannot be used.
                if (R < dest) {
                    if (rem[idx] > 0)
                        return false; // supply left but no valid destination.
                    continue;
                }
                // Use as many passengers from this segment as possible.
                ll use = min(capacity, rem[idx]);
                rem[idx] -= use;
                capacity -= use;
                // If the segment still has supply left, push it back.
                if (rem[idx] > 0) {
                    pq.push({R, idx});
                }
            }
            // It's okay if capacity > 0; that just means this carriage isn't full.
        }
        // After processing all destination carriages, check if all supply is assigned.
        for (ll r : rem) {
            if (r > 0) return false;
        }
        return true;
    };
    
    // Binary search for the minimal Z.
    while (lo <= hi){
        ll mid = (lo + hi) / 2;
        if (canDo(mid)){
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
