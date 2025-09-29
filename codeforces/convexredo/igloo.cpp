#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Walrus {
    ll a, b;
    int id;
    ll eval(ll t) const { return a + b * t; }
};

// Each block stores (time, leader_id) events
struct Block {
    vector<Walrus> lines;
    vector<pair<ll,int>> leaders; // (time_start, id)

    // Precompute leader schedule
    void build() {
        sort(lines.begin(), lines.end(), [](auto &x, auto &y){
            if (x.b != y.b) return x.b < y.b; // sort by slope
            return x.a > y.a;
        });
        vector<Walrus> hull;
        for (auto &ln : lines) {
            if (!hull.empty() && hull.back().b == ln.b) continue;
            while (hull.size() >= 2) {
                auto l1 = hull[hull.size()-2];
                auto l2 = hull[hull.size()-1];
                // Intersection of l1,l2 vs l2,ln
                long double x12 = (long double)(l2.a - l1.a) / (l1.b - l2.b);
                long double x23 = (long double)(ln.a - l2.a) / (l2.b - ln.b);
                if (x12 >= x23) hull.pop_back();
                else break;
            }
            hull.push_back(ln);
        }
        // Build leader schedule
        leaders.clear();
        for (int i=0;i<(int)hull.size();i++) {
            ll start = (i==0 ? 0 : (ll)ceil((long double)(hull[i].a - hull[i-1].a) / (hull[i-1].b - hull[i].b)));
            leaders.push_back({start, hull[i].id});
        }
    }

    // Get current leader at time t
    int getLeader(ll t) {
        int l=0,r=(int)leaders.size()-1;
        while(l<r){
            int m=(l+r+1)/2;
            if (leaders[m].first <= t) l=m;
            else r=m-1;
        }
        return leaders[l].second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q; cin>>n>>q;
    vector<Walrus> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i].a>>arr[i].b;
        arr[i].id=i+1;
    }

    int B = max(1,(int)sqrt(n));
    int numBlocks = (n+B-1)/B;
    vector<Block> blocks(numBlocks);

    for(int i=0;i<n;i++) {
        blocks[i/B].lines.push_back(arr[i]);
    }
    for(int i=0;i<numBlocks;i++) blocks[i].build();

    while(q--){
        int L,R; ll t;
        cin>>L>>R>>t; L--; R--;
        ll bestVal = LLONG_MIN;
        int bestId = -1;

        for(int b=0;b<numBlocks;b++){
            int l=b*B, r=min(n-1,(b+1)*B-1);
            if (r<L || R<l) continue;
            if (L<=l && r<=R) {
                int id = blocks[b].getLeader(t);
                ll val = arr[id-1].eval(t);
                if (val>bestVal) {bestVal=val; bestId=id;}
            } else {
                for(int i=max(L,l);i<=min(R,r);i++) {
                    ll val = arr[i].eval(t);
                    if (val>bestVal) {bestVal=val; bestId=i+1;}
                }
            }
        }
        cout<<bestId<<"\n";
    }
}

// build werteh eveloptwby that lines wr

// 