
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int q;
    cin >> q;

    vector<int> lastChange(n, -1);

    int lastGlobal = -1;
    int globalType = 0;

    for (int i = 0; i < q; i++) {
        int t, x;
        char c;
        cin >> t >> x >> c;

        if (t == 1) {
            --x;
            s[x] = c;
            lastChange[x] = i;
        } else {
            lastGlobal = i;
            globalType = t;
        }
    }

    for (int i = 0; i < n; i++) {
        if (lastChange[i] < lastGlobal) {
            if (globalType == 2) {
                s[i] = tolower(s[i]);
            } else if (globalType == 3) {
                s[i] = toupper(s[i]);
            }
        }
    }

    cout << s << '\n';
    return 0;
}

// ers weptf seri hi
/w 