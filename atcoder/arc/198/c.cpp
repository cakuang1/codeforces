#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N), B(N);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    vector<pair<int,int>> ans;

    // Performs the original operation.
    auto op = [&](int i, int j) {
        if (i > j) swap(i, j);

        ll x = A[i];
        ll y = A[j];

        A[i] = y - 1;
        A[j] = x + 1;

        ans.push_back({i, j});
    };

    // N = 2 is special:
    // applying (0,1) twice returns to the original array.
    if (N == 2) {
        if (A == B) {
            cout << "Yes\n0\n";
            return 0;
        }

        op(0, 1);

        if (A == B) {
            cout << "Yes\n";
            cout << 1 << '\n';
            cout << "1 2\n";
        } else {
            cout << "No\n";
        }

        return 0;
    }

    ll sumA = accumulate(A.begin(), A.end(), 0LL);
    ll sumB = accumulate(B.begin(), B.end(), 0LL);

    if (sumA != sumB) {
        cout << "No\n";
        return 0;
    }

    // Swap the actual values A[x] and A[y]
    // while leaving every other position unchanged.
    auto real_swap = [&](int x, int y) {
        if (x == y) return;
        if (x > y) swap(x, y);

        // If there is a position to the left, use it as helper.
        //
        // (0,y), (0,x), (0,y)
        if (x > 0) {
            op(0, y);
            op(0, x);
            op(0, y);
        }

        // Otherwise, if there is a position to the right,
        // use it as helper.
        //
        // (x,N-1), (y,N-1), (x,N-1)
        else if (y < N - 1) {
            op(x, N - 1);
            op(y, N - 1);
            op(x, N - 1);
        }

        // Only remaining case: x = 0, y = N-1.
        else {
            op(0, N - 1);
            op(0, 1);
            op(1, N - 1);
            op(0, 1);
            op(0, N - 1);
        }
    };

    /*
        Move one unit from y to x:

            A[x] += 1
            A[y] -= 1

        If x < y:

            operation(x,y):
                (a,b) -> (b-1,a+1)

            then true swap:
                -> (a+1,b-1)

        If x > y, do those steps in the opposite order.
    */
    auto transfer = [&](int x, int y) {
        // x needs +1
        // y needs -1

        if (x < y) {
            op(x, y);
            real_swap(x, y);
        } else {
            real_swap(x, y);
            op(y, x);
        }
    };

    while (true) {
        int need = -1;     // A[i] < B[i]
        int excess = -1;   // A[i] > B[i]

        for (int i = 0; i < N; i++) {
            if (A[i] < B[i]) need = i;
            if (A[i] > B[i]) excess = i;
        }

        if (need == -1) break;

        transfer(need, excess);
    }

    // Safety check
    if (A != B || ans.size() > 31000) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    cout << ans.size() << '\n';

    for (auto [i, j] : ans) {
        cout << i + 1 << ' ' << j + 1 << '\n';
    }

    return 0;
}
// wrissos mfp alsinsom
// wrsd suw
// ews a palsin e
/w si wrw