#include <bits/stdc++.h>
using namespace std;

// 2-SAT on m variables (toppings), n clauses (people)
// Variable x_i:
//   literal  2*(i-1)     means x_i = true  (topping i included)
//   literal  2*(i-1) ^ 1 means x_i = false (topping i not included)
int m;
vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, comp;

void dfs1(int u) {
    used[u] = true;
    for (int v : g[u])
        if (!used[v])
            dfs1(v);
    order.push_back(u);
}

void dfs2(int u, int cid) {
    comp[u] = cid;
    for (int v : gr[u])
        if (comp[v] == -1)
            dfs2(v, cid);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> m;

    // build implication graph on 2*m vertices
    g .assign(2*m, {});
    gr.assign(2*m, {});

    auto literal = [&](char sign, int x){
        // '+' x  => x_true  => 2*(x-1)
        // '-' x  => x_false => 2*(x-1)^1
        int idx = 2*(x-1);
        return (sign == '+' ? idx : idx^1);
    };

    auto addImp = [&](int u, int v){
        // u => v
        g[u].push_back(v);
        gr[v].push_back(u);
    };

    for(int i = 0; i < n; i++){
        char s1, s2;
        int x1, x2;
        cin >> s1 >> x1 >> s2 >> x2;
        int L1 = literal(s1, x1);
        int L2 = literal(s2, x2);
        // clause (L1 ∨ L2) gives:
        // (¬L1 -> L2) and (¬L2 -> L1)
        addImp(L1^1, L2);
        addImp(L2^1, L1);
    }

    // Kosaraju 1st pass: build order by finish time
    used.assign(2*m, false);
    order.clear();
    for(int i = 0; i < 2*m; i++){
        if(!used[i])
            dfs1(i);
    }

    // 2nd pass: assign components
    comp.assign(2*m, -1);
    int cid = 0;
    for(int i = 2*m-1; i >= 0; i--){
        int u = order[i];
        if(comp[u] == -1)
            dfs2(u, cid++);
    }

    
    // check for conflicts and build assignment
    vector<char> ans(m);
    for(int i = 0; i < m; i++){
        if(comp[2*i] == comp[2*i+1]){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        // whichever literal’s component is “higher” wins
        ans[i] = (comp[2*i] > comp[2*i+1] ? '+' : '-');
    }
    // output m symbols
    for(char c : ans)
        cout << c;
    cout << "\n";
    return 0;
}
 
// tahts ch