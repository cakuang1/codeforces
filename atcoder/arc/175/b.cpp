#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long A, B;
    string S;

    cin >> N >> A >> B >> S;

    long long unmatchedClose = 0;
    long long unmatchedOpen = 0;

    // Remove every already-valid matched pair.
    for (char c : S) {
        if (c == '(') {
            unmatchedOpen++;
        } else {
            if (unmatchedOpen > 0) {
                unmatchedOpen--;
            } else {
                unmatchedClose++;
            }
        }
    }

    // Remaining characters have the form:
    // )))...(((...
    //
    // Number of ')' that must become '('.
    long long needOpen = (unmatchedClose + 1) / 2;

    // Number of '(' that must become ')'.
    long long needClose = (unmatchedOpen + 1) / 2;

    // One swap fixes one of each type.
    long long swaps = min(needOpen, needClose);

    // A swap can also be simulated by two replacements.
    long long answer =
        swaps * min(A, 2 * B) +
        (needOpen - swaps) * B +
        (needClose - swaps) * B;

    cout << answer << '\n';
}
// 