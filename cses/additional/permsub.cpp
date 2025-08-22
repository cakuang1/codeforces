#include <bits/stdc++.h>
using namespace std;

struct Node {
    int length;  // best LIS length ending here
    int idx;     // which a‑index gave that best
};

Node combine(const Node &a, const Node &b) {
    // return the one with larger length
    return (a.length > b.length ? a : b);
}

struct SegTree {
    int n;
    vector<Node> st;
    SegTree(int _n): n(_n), st(4*n+4, {0,-1}) {}

    // point update: at position p set to max(st[p], val)
    void update(int p, const Node &val){ update(1,1,n,p,val); }
    void update(int node, int L, int R, int p, const Node &val){
        if(L==R){
            st[node] = combine(st[node], val);
            return;
        }
        int mid=(L+R)>>1;
        if(p<=mid) update(node<<1, L, mid, p, val);
        else        update(node<<1|1,mid+1,R,p,val);
        st[node] = combine(st[node<<1], st[node<<1|1]);
    }

    // range max query on [i..j]
    Node query(int i, int j){ return query(1,1,n,i,j); }
    Node query(int node, int L, int R, int i, int j){
        if(j< L || R< i) return {0,-1};
        if(i<=L && R<=j) return st[node];
        int mid=(L+R)>>1;
        return combine(
            query(node<<1,  L,    mid, i, j),
            query(node<<1|1, mid+1,R,   i, j)
        );
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for(int i=0;i<n;i++) cin >> A[i];
    for(int i=0;i<m;i++) cin >> B[i];

    // Build position map for B
    // B is a permutation of 1..m (distinct values)
    unordered_map<int,int> posB;
    posB.reserve(m*2);
    for(int i=0;i<m;i++){
        posB[B[i]] = i+1;  // 1-based for segtree
    }

    // segtree over positions 1..m
    SegTree seg(m);

    // parent pointers for reconstruction
    vector<int> parent(n, -1);
    // best DP index so far
    Node bestAll = {0,-1};

    for(int i=0;i<n;i++){
        auto it = posB.find(A[i]);
        if(it == posB.end()){
            // A[i] is not in B → cannot be in common subsequence
            continue;
        }
        int p = it->second;
        // DP: dp[i] = 1 + max_{q < p} dp[ inv[q] ]
        Node q = {0,-1};
        if(p>1) q = seg.query(1, p-1);
        Node cur = { q.length + 1, i };
        parent[i] = q.idx;  

        // update at position p
        seg.update(p, cur);

        // track global best
        if(cur.length > bestAll.length){
            bestAll = cur;
        }
    }

    // wwmax weiw er=m areaw
    // bestAll.length is the LCS length
    cout << bestAll.length << "\n";
    // reconstruct one subsequence
    vector<int> subseq;
    for(int i = bestAll.idx; i != -1; i = parent[i]){
        subseq.push_back( A[i] );
    }
    reverse(subseq.begin(), subseq.end());
    for(int x : subseq){
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
