#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1 << 18;

int n;
int a[MAXN];
pair<int,int> mx[MAXN]; // top two indices for each mask

vector<int> cur;

bool cmp(int x, int y) {
    return a[x] > a[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < (1 << n); i++) cin >> a[i];

    for (int i = 0; i < (1 << n); i++) {
        cur.clear();
        cur.push_back(i);
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                int x = i ^ (1 << j);
                cur.push_back(mx[x].first);
                if (mx[x].second != -1) cur.push_back(mx[x].second);
            }
        }
        // sort by value and remove duplicates
        sort(cur.begin(), cur.end(), cmp);
        cur.erase(unique(cur.begin(), cur.end()), cur.end());
        if (cur.size() == 1) mx[i] = {cur[0], -1};
        else mx[i] = {cur[0], cur[1]};
    }

    ll now = 0;
    for (int i = 1; i < (1 << n); i++) {
        if (mx[i].second != -1) {
            now = max(now, (ll)a[mx[i].first] + a[mx[i].second]);
        }
        cout << now << "\n";
    }
    return 0;
}
