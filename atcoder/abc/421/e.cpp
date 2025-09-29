#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using State = vector<int>; // multiset of kept dice, sorted

int faces[6]; // the 6 face values
map<pair<int, State>, double> memo;

// compute the best score from a completed set of 5 dice
double score(const State &S) {
    map<int,int> cnt;
    for (int x : S) cnt[x]++;
    double best = 0;
    for (auto [v, c] : cnt) {
        best = max(best, 1.0 * v * c);
    }
    return best;
}

  // sruely wrthis shoudltn wrwor kwe
double f(int k, State S) {
    auto key = make_pair(k, S);
    if (memo.count(key)) return memo[key];
    
    int kept = (int)S.size();
    if (k == 0 || kept == 5) {
        // game ends: must fill with remaining dice randomly
        while ((int)S.size() < 5) S.push_back(0); // placeholder
        return memo[key] = score(S);
    }
    if (k == 1) {
        // last roll: roll remaining dice once, take final score
        int m = 5 - kept;
        double res = 0.0;
        // brute force all outcomes (6^m)
        vector<int> cur(m, 0);
        function<void(int, State&)> dfs = [&](int idx, State &now) {
            if (idx == m) {
                res += score(now);
                return;
            }
            for (int fval : faces) {
                now.push_back(fval);
                dfs(idx+1, now);
                now.pop_back();
            }
        };
        State temp = S;
        dfs(0, temp);
        double prob = pow(6.0, -(m));
        return memo[key] = res * prob;
    }

    //wpobapibsptwt er

    // base w  ewhat i st he er
    // w
    // general case: still >=2 rolls
    int m = 5 - kept;
    double res = 0.0;
    vector<int> cur(m, 0);
    function<void(int, State&)> dfs = [&](int idx, State &now) {
        if (idx == m) {
            // now is S ∪ P (rolled dice added)
            // we must choose subset T of P to keep
            vector<int> rolled;
            for (int i = kept; i < (int)now.size(); i++) rolled.push_back(now[i]);
            int R = rolled.size();
            double best = 0.0;
            for (int mask = 0; mask < (1<<R); mask++) {
                State next = S;
                for (int i = 0; i < R; i++) if (mask & (1<<i)) next.push_back(rolled[i]);
                sort(next.begin(), next.end());
                best = max(best, f(k-1, next));
            }
            res += best;
            return;
        }
        for (int fval : faces) {
            now.push_back(fval);
            dfs(idx+1, now);
            now.pop_back();
        }
    };
    State temp = S;
    dfs(0, temp);
    double prob = pow(6.0, -(m));
    return memo[key] = res * prob;
}


// you weahave an empwtweteset e
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 6; i++) cin >> faces[i];
    State empty;
    cout << fixed << setprecision(10) << f(3, empty) << "\n";
    return 0;
}
 
