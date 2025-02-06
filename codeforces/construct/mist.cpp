#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

static const int MAXM = 50;

int main()
{
    srand(1);

    int a[4];
    scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);

    int M = std::max(2, std::min(MAXM, *std::max_element(a, a + 4)));
    std::vector<std::string> g;

    for (int k = 0; k < 4; ++k) {
        int islands = a[(k + 1) % 4] - 1;
        std::string s(M, 'A' + k);
        std::vector<std::pair<int, int>> pos;

        g.push_back(s);
        for (int x = 0; x < (islands + (M - 2)) / (M - 1); ++x) {
            for (int i = 0; i < 3; ++i) g.push_back(s);
            for (int i = (x & 1); i < M - !(x & 1); ++i)
                pos.push_back({(int)g.size() - 2 - ((i ^ x) & 1), i});
        }

        std::random_shuffle(pos.begin(), pos.end());
        for (int i = 0; i < islands; ++i)
            g[pos[i].first][pos[i].second] = 'A' + (k + 1) % 4;
    }

    if (g.size() <= M) {
        printf("%lu %d\n", g.size(), M);
        for (int i = 0; i < g.size(); ++i) puts(g[i].c_str());
    } else {
        printf("%d %lu\n", M, g.size());
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < g.size(); ++j) putchar(g[j][i]);
            putchar('\n');
        }
    }

    return 0;
}

#include <bits/stdc++.h>
 
using namespace std;

using ll = long long;
const int MOD2 =  998244353; 
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001; //check the limits, dummy


ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
        if (power % 2 == 1) cur = cur * base;
        cur = cur % MOD;
        return cur;
    }
}

ll inv(ll base) {
	return modExp(base, MOD-2);
}


ll mul(ll A, ll B) {
	return (A*B)%MOD;
}

ll add(ll A, ll B) {
	return (A+B)%MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll sub(ll A, ll B) {
    return (A-B+MOD)%MOD;
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

ll choose(ll a, ll b) {
	if (b > a) return 0;
	if (a < 0) return 0;
	if (b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a-b]);
    return cur;
}

void initFacs() {
	facs[0] = 1;
	facInvs[0] = 1;
	for (int i = 1 ; i < MOD ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}



int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    

    

  	return 0;
}
 

