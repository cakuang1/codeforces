#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 4e18;

int n, k;
vector<ll> pref;
vector<ll> dp_prev, dp_cur;

inline ll cost(int j, int i) {
    ll sum = pref[i] - pref[j];
    return sum * sum;
}

// detnerin e number pf distinc telemts w 
// wwhow woudl oyu oslve hits rw
// we
void compute(int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<ll,int> best = {INF, -1};

    // search only within [optL, optR]
    for (int j = optL; j <= min(mid - 1, optR); j++) {
        ll val = dp_prev[j] + cost(j, mid);
        if (val < best.first) {
            best = {val, j};
        }
    }

    dp_cur[mid] = best.first;
    int opt = best.second;
    compute(l, mid - 1, optL, opt);
    compute(mid + 1, r, opt, optR);
}

// kth later wr 

// kth ww must wehcoose we w we

// cost i < n is what?

// wwhat wrthwe
// gneral weoutlien we
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    vector<ll> a(n+1);
    pref.assign(n+1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }

    dp_prev.assign(n+1, INF);
    dp_prev[0] = 0;

    for (int g = 1; g <= k; g++) {
        dp_cur.assign(n+1, INF);
        compute(1, n, 0, n-1);
        dp_prev.swap(dp_cur);
    }

    cout << dp_prev[n] << "\n";
    return 0;
}

// wqudractwr n wr