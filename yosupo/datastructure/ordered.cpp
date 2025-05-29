#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;
using namespace __gnu_pbds;

// ordered_set supports insert, erase, order_of_key, find_by_order,
// plus the usual lower_bound/upper_bound
template<class T>
using ordered_set = tree<
    T, 
    null_type, 
    less<T>, 
    rb_tree_tag, 
    tree_order_statistics_node_update
>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    ordered_set<ll> s;
    // read initial elements
    for(int i = 0; i < N; i++){
        ll a;
        cin >> a;
        s.insert(a);
    }

    while(Q--){
        int type;
        ll x;
        cin >> type >> x;

        if(type == 0){
            // insert x if not present
            s.insert(x);
        }
        else if(type == 1){
            // erase x if present
            s.erase(x);
        }
        else if(type == 2){
            // x-th smallest (1-based)
            if(x >= 1 && x <= (ll)s.size()){
                auto it = s.find_by_order(x - 1);
                cout << *it << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
        else if(type == 3){
            // count elements <= x
            // order_of_key(x+1) counts elements < x+1 ⇒ ≤ x
            cout << s.order_of_key(x + 1) << "\n";
        }
        else if(type == 4){
            // predecessor: largest element ≤ x
            auto it = s.upper_bound(x);
            if(it == s.begin()){
                cout << -1 << "\n";
            } else {
                --it;
                cout << *it << "\n";
            }
        }
        else if(type == 5){
            // successor: smallest element ≥ x
            auto it = s.lower_bound(x);
            if(it == s.end()){
                cout << -1 << "\n";
            } else {
                cout << *it << "\n";
            }
        }
    }

    return 0;
}
