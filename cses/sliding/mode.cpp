#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }

    unordered_map<int,int> cnt;
    cnt.reserve(k*2);
    // set of { -count, value }
    set<pair<int,int>> S;

    auto add = [&](int v){
        if(auto it = cnt.find(v); it != cnt.end()){
            S.erase({ -it->second, v });
            it->second++;
        } else {
            cnt[v] = 1;
        }
        S.insert({ -cnt[v], v });
    };
    auto remove = [&](int v){
        auto it = cnt.find(v);
        S.erase({ -it->second, v });
        it->second--;
        if(it->second > 0){
            S.insert({ -it->second, v });
        } else {
            cnt.erase(it);
        }
    };

    // build first window
    for(int i = 0; i < k; i++){
        add(x[i]);
    }

    vector<int> ans;
    ans.reserve(n - k + 1);
    ans.push_back(S.begin()->second);

    // slide
    for(int i = k; i < n; i++){
        remove(x[i-k]);
        add(x[i]);
        ans.push_back(S.begin()->second);
    }

    // output
    for(int i = 0; i < (int)ans.size(); i++){
        cout << ans[i] << (i+1<(int)ans.size()?' ':'\n');
    }
    return 0;
}

