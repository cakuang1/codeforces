#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int const maxn = 2e5 + 5, max_val = 2e5 + 5;
ll mod = 1e9 + 7, ans = 1;
int nxt[max_val], n;
multiset <int> cnt[max_val];
map <int, int> cnt_divisor[maxn];

void add(int i, int x) {
    while (x != 1) {
        int div = nxt[x], add = 0;
        while (nxt[x] == div) add++, x = x / nxt[x];

        int lst = cnt_divisor[i][div];
        cnt_divisor[i][div] += add;
        int lst_min = 0;
        if ((int)cnt[div].size() == n) {
            lst_min = (*cnt[div].begin());
        }
        if (lst != 0) {
            cnt[div].erase(cnt[div].find(lst));
        }
        cnt[div].insert(lst + add);
        if ((int)cnt[div].size() == n) {
            for (int j = lst_min + 1; j <= (*cnt[div].begin()); ++j) {
                ans = ans * (ll)div % mod;
            }
        }
    }
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q, l, x;
    cin >> n >> q;

    for (int i = 2; i < maxn; ++i) {
        if (nxt[i] == 0) {
            nxt[i] = i;
            if (i > 10000) continue;
            for (int j = i * i; j < maxn; j += i) {
                if (nxt[j] == 0) nxt[j] = i;
            }
        }
    }
    // how many possible tw    
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        add(i, x);
    }

    for (int i = 1; i <= q; ++i) {
        cin >> l >> x;
        add(l, x);
        cout << ans << '\n';
    }

    return 0;
} 


 
//  wcreally weyo uwwan to extend 
// lcm is defined was the amx  weof er werwwwho wmay wmany w