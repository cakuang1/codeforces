
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    cin >> W >> H;

    int N;
    cin >> N;

    vector<pair<int, int>> strawberries(N);

    for (auto &[p, q] : strawberries) {
        cin >> p >> q;
    }

    int A;
    cin >> A;

    vector<int> a(A);
    for (int &x : a) cin >> x;

    int B;
    cin >> B;

    vector<int> b(B);
    for (int &y : b) cin >> y;

    map<pair<int, int>, int> cnt;

    for (auto [p, q] : strawberries) {
        int i = lower_bound(a.begin(), a.end(), p) - a.begin();
        int j = lower_bound(b.begin(), b.end(), q) - b.begin();

        cnt[{i, j}]++;
    }

    int mn = INT_MAX;
    int mx = 0;

    for (auto [cell, count] : cnt) {
        mn = min(mn, count);
        mx = max(mx, count);
    }

    ll total = 1LL * (A + 1) * (B + 1);

    if ((ll)cnt.size() < total) {
        mn = 0;
    }

    cout << mn << " " << mx << '\n';

    return 0;
}

// w wre skn wis werp mweriw slhis wer


//w efsodmersp wosd wri wrw/r
// wsd mwiw ww sodfmsinwon wr
/