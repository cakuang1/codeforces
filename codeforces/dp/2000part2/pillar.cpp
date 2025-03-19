#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Structure for segment tree nodes.
struct Node {
    int best; // best dp value in this segment
    int idx;  // index that achieved that dp value
};

// Segment tree for range maximum queries.
struct SegTree {
    int size;
    vector<Node> tree;
    
    // Initialize segment tree with at least n leaves.
    SegTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {0, -1});
    }
    
    // Update position pos (0-indexed) with new dp value if it's higher.
    void update(int pos, int val, int idx) {
        pos += size;
        if (val > tree[pos].best) {
            tree[pos] = {val, idx};
        }
        for (pos /= 2; pos >= 1; pos /= 2) {
            if (tree[2*pos].best >= tree[2*pos+1].best)
                tree[pos] = tree[2*pos];
            else
                tree[pos] = tree[2*pos+1];
        }
    }
    
    // Query maximum dp value and index in the range [l, r] (0-indexed).
    Node query(int l, int r) {
        Node res = {0, -1};
        l += size; r += size;
        while (l <= r) {
            if (l % 2 == 1) {
                if (tree[l].best > res.best)
                    res = tree[l];
                l++;
            }
            if (r % 2 == 0) {
                if (tree[r].best > res.best)
                    res = tree[r];
                r--;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    ll d;
    cin >> n >> d;
    
    vector<ll> h(n);
    for (int i = 0; i < n; i++){
        cin >> h[i];
    }
    
    // Compress the heights.
    vector<ll> comp = h;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int m = comp.size();
    
    // Lambda to get compressed index.
    auto getPos = [&](ll x) -> int {
        return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin());
    };
    
    // For the "low" query: we want the largest index with value <= (h[i] - d).
    auto getLowBound = [&](ll x) -> int {
        // upper_bound returns first element > x, so subtract one.
        int pos = int(upper_bound(comp.begin(), comp.end(), x) - comp.begin()) - 1;
        return pos; // may be -1 if no element <= x.
    };
    
    // For the "high" query: we want the smallest index with value >= (h[i] + d).
    auto getHighBound = [&](ll x) -> int {
        int pos = int(lower_bound(comp.begin(), comp.end(), x) - comp.begin());
        return pos; // may be m if no element >= x.
    };
    
    // dp[i] = length of best jump sequence ending at pillar i.
    // parent[i] stores the previous pillar index in the sequence.
    vector<int> dp(n, 0), parent(n, -1);
    
    // Create the segment tree over the compressed height positions.
    SegTree seg(m);
    
    int bestOverall = 0, bestIdx = -1;
    // Process pillars in order (which respects the index order requirement).
    for (int i = 0; i < n; i++){
        int pos = getPos(h[i]);
        int bestCandidate = 0;
        int candidateIdx = -1;
        
        // Query the "lower" range: pillars with height <= h[i] - d.
        int lowPos = getLowBound(h[i] - d);
        if (lowPos >= 0) {
            Node res = seg.query(0, lowPos);
            if (res.best > bestCandidate) {
                bestCandidate = res.best;
                candidateIdx = res.idx;
            }
        }
        
        // Query the "higher" range: pillars with height >= h[i] + d.
        int highPos = getHighBound(h[i] + d);
        if (highPos < m) {
            Node res = seg.query(highPos, m-1);
            if (res.best > bestCandidate) {
                bestCandidate = res.best;
                candidateIdx = res.idx;
            }
        }
        
        // Set dp[i] to one more than the best candidate found (or 1 if none found).
        dp[i] = bestCandidate + 1;
        parent[i] = candidateIdx;
        
        // Update the segment tree at the compressed height position.
        seg.update(pos, dp[i], i);
        
        // Update overall best result.
        if (dp[i] > bestOverall) {
            bestOverall = dp[i];
            bestIdx = i;
        }
    }
    
    // Reconstruct the jump sequence.
    vector<int> sequence;
    for (int cur = bestIdx; cur != -1; cur = parent[cur]) {
        sequence.push_back(cur + 1); // convert 0-indexed to 1-indexed for output
    }
    reverse(sequence.begin(), sequence.end());
    
    cout << bestOverall << "\n";
    for (int x : sequence)
        cout << x << " ";
    cout << "\n";
     return 0;
}
