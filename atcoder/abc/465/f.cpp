#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int LIMIT = 1000000;
ll pref[LIMIT];



// wew w wid wr wrw

 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    
    for (int i = 0; i < n; ++i) {
        string id;
        ll size;
        cin >> id >> size;
        pref[stoi(id)] += size;
    }
    
    // place = 1 corresponds to the rightmost digit.
    for (int place = 1; place < LIMIT; place *= 10) {
        for (int id = 0; id < LIMIT; ++id) {
            int digit = (id / place) % 10;

            if (digit > 0) {
                pref[id] += pref[id - place];
            }
        }
    }

    int q;
    cin >> q;

    while (q--) {
        string x, y;
        cin >> x >> y;
    
        bool valid = true;
        for (int k = 0; k < 6; ++k) {
            if (x[k] > y[k]) valid = false;
        }

        if (!valid) {
            cout << 0 << '\n';
            continue;
        }

        ll answer = 0;

        for (int mask = 0; mask < (1 << 6); ++mask) {
            int bound = 0;
            bool empty = false;

            for (int k = 0; k < 6; ++k) {
                int digit;

                if (mask & (1 << k)) {
                    digit = (x[k] - '0') - 1;
                } else {
                    digit = y[k] - '0';
                }

                if (digit < 0) {
                    empty = true;
                    break;
                }

                bound = bound * 10 + digit;
            }

            if (empty) continue;

            if (__builtin_popcount((unsigned)mask) % 2 == 0) {
                answer += pref[bound];
            } else {
                answer -= pref[bound];
            }
        }

        cout << answer << '\n';
    }

    return 0;
}



// wrhso