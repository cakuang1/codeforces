#include <bits/stdc++.h>
using namespace std;

// Persistent tree for parity: leaves hold 0/1; internal nodes just hold children.
// We rely on pointer equality to detect identical subtrees between two versions.
struct Node {
    Node *l, *r;
    unsigned char bit; // only meaningful at leaves (0/1). Internal nodes don't need any aggregate.
    Node(Node* L=nullptr, Node* R=nullptr, unsigned char b=0): l(L), r(R), bit(b) {}
};

int n, q;
vector<int> a, vals;     // a: original values; vals: compressed->original map
vector<int> comp;        // original->compressed
vector<Node*> root;      // root[i] = version for prefix [1..i]

// Build a full zero tree over [1..M].
Node* build(int L, int R){
    if(L == R) return new Node(nullptr, nullptr, 0);
    int mid = (L+R)>>1;
    return new Node(build(L,mid), build(mid+1,R), 0);
}

// Toggle leaf at position pos in version 'prev'.
Node* update(Node* prev, int L, int R, int pos){
    if(L == R){
        // flip the leaf bit
        return new Node(nullptr, nullptr, prev->bit ^ 1);
    }
    int mid = (L+R)>>1;
    if(pos <= mid){
        Node* nl = update(prev->l, L, mid, pos);
        // right child unchanged (shared)
        return new Node(nl, prev->r, 0);
    }else{
        Node* nr = update(prev->r, mid+1, R, pos);
        // left child unchanged (shared)
        return new Node(prev->l, nr, 0);
    }
}




int firstDiff(Node* A, Node* B, int L, int R){
    if(A == B) return -1;          // entire segment identical → no difference here
    if(L == R) return L;           // leaf differs → this is the smallest differing index
    int mid = (L+R)>>1;
    // Prefer left: if left subtrees are equal, smallest diff must be in right
    int leftAns = firstDiff(A->l, B->l, L, mid);
    if(leftAns != -1) return leftAns;
    return firstDiff(A->r, B->r, mid+1, R);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n+1);
    vector<int> all(n);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        all[i-1] = a[i];
    }
    // coordinate compression
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    auto getId = [&](int x){
        return int(lower_bound(all.begin(), all.end(), x) - all.begin()) + 1; // 1..M
    };
    int M = (int)all.size();
    for(int i=1;i<=n;i++) a[i] = getId(a[i]); // compress
    vals = all; // vals[idx-1] = original value for compressed idx

    // Build persistent versions
    root.resize(n+1);
    root[0] = build(1, M);
    for(int i=1;i<=n;i++){
        root[i] = update(root[i-1], 1, M, a[i]); // toggle parity of value a[i]
    }

    cin >> q;
int last = 0;
while (q--) {
    int A, B; 
    cin >> A >> B;
    int l = A ^ last;
    int r = B ^ last;
    if (l > r) swap(l, r);

    if (l < 1) l = 1;
    if (r > n) r = n;
    // 
    Node* leftRoot = (l > 0 ? root[l-1] : root[0]);
    Node* rightRoot = root[r];

    int idx = firstDiff(leftRoot, rightRoot, 1, M);
    int ans = (idx == -1 ? 0 : vals[idx-1]);

    cout << ans << '\n';
    last = ans;
}
    return 0; 
}



// wsriet