#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 2e5 + 10;

PII p[N];
int s[N], s1[N], s2[N];

void solve() {
    int n, m;
    scanf("%d %d %*d", &n, &m);
    memset(s, 0, n + 10 << 2);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        s[l]++, s[r + 1]--;
        p[i] = {l, r};
    }
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= n; i++) {
        s[i] += s[i - 1];    // 下标i被覆盖的次数
        s1[i] = s1[i - 1] + (s[i] == 1);    // 前缀中s[i]=1的下标数量
        s2[i] = s2[i - 1] + (s[i] == 2);    // 前缀中s[i]=2的下标数量
    }
    int m1 = 0, m2 = 0;    // 找到含s[i]=1的下标最多的两个区间
    for (int i = 1; i <= m; i++) {
        int t = s1[p[i].second] - s1[p[i].first - 1];
        if (t >= m1) m2 = m1, m1 = t;
        else if (t > m2) m2 = t;
    }
    int ret = m1 + m2;
    multiset<PII> st;
    for (int i = 1, j = 1; i <= n; i++) {
        if (s[i] == 2) {    // i被覆盖了两次
            while (j <= m && p[j].first <= i) {    // 把左端点不超过i的区间加进来
                st.insert({p[j].second, p[j].first});
                j++;
            }
            while (!st.empty() && st.begin()->first < i) {    // 删掉右端点小于i的区间
                st.erase(st.begin());
            }
            // 此时集合的大小一定恰好是2
            int l = max(st.begin()->second, st.rbegin()->second);
            int r = min(st.begin()->first, st.rbegin()->first);
            int t = s2[r] - s2[l - 1];    // 两个区间的交集中s[i]=2的下标数量
            l = min(st.begin()->second, st.rbegin()->second);
            r = max(st.begin()->first, st.rbegin()->first);
            t += s1[r] - s1[l - 1];    // 两个区间的并集中s[i]=1的下标数量
            ret = max(ret, t);
        }
    }
    printf("%d\n", ret + count(s + 1, s + n + 1, 0));    // 加上s[i]=0的下标数量
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    
    return 0;
} 
// please calcultte te hs ums w