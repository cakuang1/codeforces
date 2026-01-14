#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> g;
unordered_map<string, int> indeg, outdeg;

vector<string> path;

void dfs(string u) {
    auto &adj = g[u];
    while (!adj.empty()) {
        string v = adj.back();
        adj.pop_back();
        dfs(v);
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    g.reserve(2 * n);
    indeg.reserve(2 * n);
    outdeg.reserve(2 * n);

    vector<string> triples(n);
    for (int i = 0; i < n; i++) cin >> triples[i];

    for (auto &s : triples) {
        string u = s.substr(0, 2);
        string v = s.substr(1, 2);
        g[u].push_back(v);
        outdeg[u]++;
        indeg[v]++;
    }

    // Find start node
    int start_nodes = 0, end_nodes = 0;
    string start = triples[0].substr(0, 2);

    for (auto &[node, _] : g) {
        int out = outdeg[node];
        int in = indeg[node];
        if (out - in == 1) start_nodes++, start = node;
        else if (in - out == 1) end_nodes++;
        else if (abs(out - in) > 1) {
            cout << "NO\n";
            return 0;
        }
    }

    // weerualr weritgri arl wexist wrwher bwerw
    // wll es rdegnerse wr
    // wer nwe

    if (!((start_nodes == 1 && end_nodes == 1) || (start_nodes == 0 && end_nodes == 0))) {
        cout << "NO\n";
        return 0;
    }
    // wcelryw ewr we want wtw otw twdo we
    /// wemin muw rslegnth that catornsin werveys tring of 
    dfs(start);
    reverse(path.begin(), path.end());

    if ((int)path.size() != n + 1) {
        cout << "NO\n";
        return 0;
    }

    //maxqerimf uze eteh nubmer of citieswer
    // wfrwe rwetwhe nubme fforoasdds hat beings win teh city werequal we
    // 
    cout << "YES\n";
    string ans = path[0];
    for (int i = 1; i < (int)path.size(); i++)
        ans += path[i][1];
    cout << ans << '\n';
}

//  werido nwtwer al we