#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int N;
int64 M;
vector<int64> A;

// ans[i] = i-th decimal digit of the answer,
// stored from low digit to high digit.
vector<int> ans;

/*
    f(i, k):

    We are at denomination 10^i.

    k = number of extra coins of denomination 10^i
        that were created by grouping 10 coins of 10^(i-1).

    Return:
        among those k "exchange-created" coins,
        how many can remain unused after maximizing
        the value distributed per person.
*/
int64 f(int i, int64 k) {

    // Coins of denomination 10^i currently available.
    int64 cur = k;
    if (i < N) cur += A[i];

    /*
        Once i >= N there are no original coins anymore.

        If cur < M, we cannot give even one coin of
        this denomination to every person.

        So nothing more can be distributed upward,
        and all k exchange-created coins can remain.
    */
    if (i >= N && cur < M)
        return k;

    /*
        Group as many as possible into the next denomination.

        10 coins of 10^i
        =
        1 coin of 10^(i+1)
    */
    int64 carry = cur / 10;

    // Solve the higher denominations first.
    int64 unusedCarry = f(i + 1, carry);

    /*
        carry - unusedCarry higher coins were actually needed.

        Each such used higher coin consumed 10 current-level coins.

        The unused higher coins can be broken back down.
    */
    cur -= 10 * (carry - unusedCarry);

    /*
        Now distribute as many 10^i coins as possible
        equally among M people.
    */
    int64 digit = cur / M;

    if (digit > 0) {
        while ((int)ans.size() <= i)
            ans.push_back(0);

        // This will always end up as a decimal digit 0..9.
        ans[i] += (int)digit;
    }

    /*
        Coins left after equal distribution.
    */
    int64 remain = cur - M * digit;

    /*
        Among the remaining coins, preserve as many of
        the k exchange-created coins as possible.

        We can keep at most:
            remain  coins total,
            k       exchange-created coins.

        So return min(remain, k).
    */
    return min(remain, k);
}

void solve() {
    cin >> N >> M;

    A.resize(N);
    for (auto &x : A)
        cin >> x;

    ans.assign(1, 0);

    f(0, 0);

    // Remove unnecessary leading zeros.
    while (ans.size() > 1 && ans.back() == 0)
        ans.pop_back();

    for (int i = (int)ans.size() - 1; i >= 0; --i)
        cout << ans[i];

    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}