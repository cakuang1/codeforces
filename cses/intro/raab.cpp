#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<long long> vl;
typedef pair<long long, long long> pl;

#define nl '\n'
#define sp ' '
#define PB push_back
#define MP make_pair
#define fori(i, a, b) for(int i=a; i<=b; i++)
#define sz(x) (int)x.size()
#define rarr(a) for(auto& x: a) cin >> x;
#define all(a) a.begin(), a.end()
#define vecin(name, len) vector<int> name(len); for (auto &_ : name) cin >> _;
#define vecout(v) for (auto _ : v) cout << _ << " "; cout << endl;

inline void fastio(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

inline void solvee(){
    int n, a, b; cin >> n >> a >> b;
    if(a+b>n){
        cout << "NO" << nl;
        return;
    }
    // lets make b sorted and focus on a
    // we want a wins and n - b+a draws // i need to pick the first a wins such that i have enough run way to also make those draws by order matching at the end
    vector<int> p, q(n);
    fori(i, 1, n){
        q[i-1] = i;
    }
    // b a n-(a+b) // breaking the sorted set by number of elements for loss win and draw for player 1
    int j=0;
    fori(i, b+1, b+a){ // a+b
        p.push_back(i);
        if(q[j] >= p[j]){
            cout << "NO" << nl;
            return;
        }
        ++j;
    }
    fori(i, 1, b){
        p.push_back(i);
        if(q[j] <= p[j]){
            cout << "NO" << nl;
            return;
        }
        j++;
    }
    fori(i, a+b+1, n){
        p.push_back(i);
        if(q[j] != p[j]){
            cout << "NO" << nl;
            return;
        }
        j++;
    }
    cout << "YES" << nl;
    vecout(p);
    vecout(q);
}

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        solvee();
    }
}
