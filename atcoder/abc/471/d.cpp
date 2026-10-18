#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    ll V;
    cin >> Q >> V;

    priority_queue<ll> pq;

    while (Q--) {
        int type;
        ll t;
        cin >> type >> t;

        if (type == 1) {
            ll w;
            cin >> w;
            pq.push(w - t);
        } else {
            if (pq.empty()) {
                cout << -1 << '\n';
            } else {
                cout << min(V, t + pq.top()) << '\n';
                pq.pop();
            }
        }
    }
}


// a1


// (a1,a2,a3)



// werwsfirwwjsi
// (a1a1,a1a2,a1a3)

// werwj sfeisdfin wer

// wersos subelf wer

// a1^2 + a2^2 + a3^3 + 2(a1,a2) w