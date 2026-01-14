#include <bits/stdc++.h>
using namespace std;

struct Word {
    int len, idx;
};

vector<string> res;
int cur = 0; // pointer to current word being assigned

// Recursive DFS builder
void dfs(vector<Word> &A, int dep, string &s, int digit) {
    if (cur >= (int)A.size()) return;

    if (dep > 0) s.push_back(char('0' + digit));

    if (dep == A[cur].len) {
        res[A[cur].idx] = s;
        cur++;
        s.pop_back();
        return;
    }

    dfs(A, dep + 1, s, 0);
    dfs(A, dep + 1, s, 1);

    if (dep > 0) s.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Word> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].len;
        A[i].idx = i;
    }

    // sort by length
    sort(A.begin(), A.end(), [](auto &a, auto &b) {
        return a.len < b.len;
    });

    res.assign(n, "");
    string tmp;
    dfs(A, 0, tmp, 0);

    if (cur >= n) {
        cout << "YES\n";
        for (auto &s : res) cout << s << "\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}

