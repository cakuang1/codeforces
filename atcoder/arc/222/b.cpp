#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve(ll a, ll b, ll c) {
    vector<ll> v = {a, b, c};
    ll ans = 0;

    // Rotate (A,B,C).
    // Each rotation handles:
    //   only Type 1
    //   Type 1 + Type 2
    for (int rot = 0; rot < 3; rot++) {
        ll A = v[rot];
        ll B = v[(rot + 1) % 3];
        ll C = v[(rot + 2) % 3];

        /*
            Only Type 1:

                n A + (n+1) B -> score n

            Reserve one B.
            Then every AB pair gives one winner.
        */
        if (B >= 1) {
            ans = max(ans, min(A, B - 1));
        }

        /*
            Type 1 + Type 2:

                Type 1: n A + (n+1) B
                Type 2: m B + (m+1) C

            Reserve:
                1 B for Type 1
                1 C for Type 2

            Remaining:
                A     copies of A
                B-1   copies of B
                C-1   copies of C

            Every score consumes either:
                AB
            or:
                BC

            Thus B is one side of every pair.

            Maximum =
                min(B-1, A + (C-1))
        */
        if (B >= 1 && C >= 1) {
            ans = max(ans, min(B - 1, A + C - 1));
        }
    }

    /*
        All three types.

        Reserve one A, one B, one C.

        Then each winner consumes one of:

            AB
            BC
            CA

        So we just want the maximum number of pairs
        of DIFFERENT types.

        Let residual counts be x,y,z.

        Maximum number of pairs is:

            min(
                (x+y+z)/2,
                (x+y+z) - max(x,y,z)
            )
    */
    if (a >= 1 && b >= 1 && c >= 1) {
        ll x = a - 1;
        ll y = b - 1;
        ll z = c - 1;

        ll sum = x + y + z;
        ll mx = max({x, y, z});

        ans = max(ans, min(sum / 2, sum - mx));
    }

    /*
        Exceptional cases:

        The entire circle can itself be one alternating group.

        ABABAB...  with A = B, C = 0
        BCBCBC...  with B = C, A = 0
        CACACA...  with C = A, B = 0

        Example:

            A B A B
            ^   ^

        Both A's win.

        The normal "substring" decomposition loses one winner
        because there is nowhere to cut the circle.
    */
    if (c == 0 && a == b)
        ans = max(ans, a);

    if (a == 0 && b == c)
        ans = max(ans, b);

    if (b == 0 && c == a)
        ans = max(ans, c);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll a, b, c;
        cin >> a >> b >> c;

        cout << solve(a, b, c) << '\n';
    }
}
