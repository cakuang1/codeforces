#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll k;
    cin >> n >> m >> k;

    vector<vector<ll>> a(n, vector<ll>(m));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        cin >> a[i][j];

    // one deque per type
    vector<deque<pair<ll,int>>> dq(m);

    ll sumMax = 0;
    int l = 0;
    int bestLen = 0;
    vector<ll> bestS(m, 0);

    // sliding window [l..r]
    for(int r = 0; r < n; r++){
        // 1) add a[r][i]
        for(int i = 0; i < m; i++){
            ll v = a[r][i];
            // pop smaller or equal from back
            while(!dq[i].empty() && dq[i].back().first <= v)
                dq[i].pop_back();
            dq[i].emplace_back(v, r);
        }

        // 2) recompute sum of current maxima
        sumMax = 0;
        for(int i = 0; i < m; i++)
            sumMax += dq[i].front().first;

        // 3) shrink from left while sumMax > k
        while(l <= r && sumMax > k){
            for(int i = 0; i < m; i++){
                // if the outgoing element was the max, pop it
                if(dq[i].front().second == l)
                    dq[i].pop_front();
            }
            l++;
            sumMax = 0;
            for(int i = 0; i < m; i++)
                sumMax += (dq[i].empty() ? 0 : dq[i].front().first);
        }

        // 4) record best
        int len = r - l + 1;
        if(len > bestLen){
            bestLen = len;
            for(int i = 0; i < m; i++)
                bestS[i] = dq[i].empty() ? 0 : dq[i].front().first;
        }
    }

    // 5) output the shot counts S_i
    //    (they automatically sum to <= k)
    for(int i = 0; i < m; i++){
        cout << bestS[i] << (i+1<m ? ' ' : '\n');
    }
    return 0;
}
