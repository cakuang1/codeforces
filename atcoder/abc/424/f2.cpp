#include <bits/stdc++.h>
using namespace std;

struct Node {
    int sum, minPref;
    Node(int s=0,int m=0): sum(s), minPref(m) {}
};

Node merge(const Node &a, const Node &b) {
    Node res;
    res.sum = a.sum + b.sum;
    res.minPref = min(a.minPref, a.sum + b.minPref);
    return res;
}

struct Segtree {
    int n;
    vector<Node> seg;
    Segtree(int n): n(n) {
        seg.assign(4*n, Node());
    }
    void update(int v,int l,int r,int pos,int val){
        if(l==r){
            seg[v].sum += val;
            seg[v].minPref = min(0, seg[v].sum);
            return;
        }
        int m=(l+r)/2;
        if(pos<=m) update(v*2,l,m,pos,val);
        else update(v*2+1,m+1,r,pos,val);
        seg[v] = merge(seg[v*2], seg[v*2+1]);
    }
    Node query(int v,int l,int r,int ql,int qr){
        if(qr<l || r<ql) return Node(0, INT_MAX/2);
        if(ql<=l && r<=qr) return seg[v];
        int m=(l+r)/2;
        Node L=query(v*2,l,m,ql,qr);
        Node R=query(v*2+1,m+1,r,ql,qr);
        return merge(L,R);
    }
};

// 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;
    cin>>N>>Q;
    Segtree st(N);

    while(Q--){
        int A,B;
        cin>>A>>B;
        Node res = st.query(1,1,N,A,B);
        if(res.sum==0 && res.minPref==0){
            cout<<"Yes\n";
            st.update(1,1,N,A,+1);
            st.update(1,1,N,B,-1);
        }else{
            cout<<"No\n";
        }
    }
}



 // wetwo wmain wcan we
// takewthe min wierm werpefix rsisf wuerw
//insne ethsie wesi werinseiandwe