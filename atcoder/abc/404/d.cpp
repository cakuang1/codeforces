#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<ll> C(N);
    for (int i = 0; i < N; i++) 
        cin >> C[i];

    vector<vector<int>> zoosOf(M);
    for (int j = 0; j < M; j++){
        int K; 
        cin >> K;
        zoosOf[j].resize(K);
        for (int t = 0; t < K; t++){
            cin >> zoosOf[j][t];
            --zoosOf[j][t];  // 0‐based
        }
    }
    
    ll ans = LLONG_MAX;
    int totalStates = 1;
    for(int i = 0; i < N; i++) totalStates *= 3;  // = 3^N

        
    vector<int> x(N);
    for (int s = 0; s < totalStates; s++){
        // decode s in base 3 → x[i] ∈ {0,1,2}
        int tmp = s;
        ll cost = 0;
        for (int i = 0; i < N; i++){
            x[i] = tmp % 3;
            tmp /= 3;
            cost += C[i] * x[i];
            if (cost >= ans) break;  // pruning
        }
        if (cost >= ans) continue;

        // check each animal j is seen ≥2 times
        bool ok = true;
        for (int j = 0; j < M; j++){
            int seen = 0;
            for (int zoo : zoosOf[j]){
                seen += x[zoo];
                if (seen >= 2) break;
            }
            if (seen < 2) { ok = false; break; }
        }
        if (ok) ans = cost;
    }

    cout << (ans==LLONG_MAX ? -1 : ans) << "\n";
    return 0;
}
