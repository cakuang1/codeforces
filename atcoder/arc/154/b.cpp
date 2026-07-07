#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S, T;
    cin >> N >> S >> T;

    vector<int> cs(26), ct(26);
    for (char c : S) cs[c - 'a']++;
    for (char c : T) ct[c - 'a']++;

    if (cs != ct) {
        cout << -1 << '\n';
        return 0;
    }

    int i = N - 1; // pointer in S

    for (int j = N - 1; j >= 0 && i >= 0; j--) {
        if (S[i] == T[j]) {
            i--;
        }
    }

    cout << i + 1 << '\n';
    return 0;
}
/// rlsosnsfusubssi w
// werho
// wershdsfsf hwrio
/ wr