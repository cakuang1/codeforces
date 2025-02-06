#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

const int Tmax=(int)2e+5;
const int Xmax=(int)2e+5;

struct S {
    int x;
};

struct F {
    int x;
};

S op(S l, S r) { return S{max(l.x,r.x)}; }

S e() { return S{0}; }

S mapping(F l, S r) { return S{l.x+r.x}; }

F composition(F l, F r) { return F{l.x+r.x}; }

F id() { return F{0}; }

int main(void) {
	int n,d,w,t,x,ans=0;
	vector<pair<int,int> >q[Tmax+1];
	cin>>n>>d>>w;
	for(int i=0;i<n;i++){
		cin>>t>>x;
		q[max(t-d,0)].push_back({x,1});
		q[t].push_back({x,-1});
	}
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(Xmax);
    for(int i=0;i<Tmax;i++){
        int sz=q[i].size();
        for(int j=0;j<sz;j++){
            seg.apply(max(0,q[i][j].first-w),q[i][j].first,F{q[i][j].second});
        }
        ans=max(ans,seg.prod(0,Xmax).x);
    }
	cout<<ans<<endl;
	return 0;
}
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

const int Tmax=(int)2e+5;
const int Xmax=(int)2e+5;

struct S {
    int x;
};

struct F {
    int x;
};

S op(S l, S r) { return S{max(l.x,r.x)}; }

S e() { return S{0}; }

S mapping(F l, S r) { return S{l.x+r.x}; }

F composition(F l, F r) { return F{l.x+r.x}; }

F id() { return F{0}; }

int main(void) {
	int n,d,w,t,x,ans=0;
	vector<pair<int,int> >q[Tmax+1];
	cin>>n>>d>>w;
	for(int i=0;i<n;i++){
		cin>>t>>x;
		q[max(t-d,0)].push_back({x,1});
		q[t].push_back({x,-1});
	}
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(Xmax);
    for(int i=0;i<Tmax;i++){
        int sz=q[i].size();
        for(int j=0;j<sz;j++){
            seg.apply(max(0,q[i][j].first-w),q[i][j].first,F{q[i][j].second});
        }
        ans=max(ans,seg.prod(0,Xmax).x);
    }
	cout<<ans<<endl;
	return 0;
}

