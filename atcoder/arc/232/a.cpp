#include <bits/stdc++.h>
using namespace std;


// wecsns=s gah


// wewtwhsdifwrw fwemor



// wewi o u splaetsi werw/

// wwpitoens agodo wrwnosd wr


/// wewTirs usnsiosf siv wr




// wtinralstsarts asors bu wr uwe 



// This sinetmsut alread contian istlesicn eesd potin wer


// wS for some u wer

// u assume we have fufillel wall we 


/ /sdf wrw wr


void solve() {
    int n, m;
    cin >> n >> m;

    // Two sentinel 1s on each side
    int N = n + 4;
    int INF = N + 10;

    vector<int> maxL(N + 2, -1);
    vector<int> minL(N + 2, INF);

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;

        l += 2;
        r += 2;

        maxL[r] = max(maxL[r], l);
        minL[r] = min(minL[r], l);
    }

    // A[z] = max L among intervals with R < z
    // B[z] = min L among intervals with R >= z
    vector<int> A(N + 2, -1), B(N + 2, INF);

    int mx = -1;
    for (int z = 1; z <= N; z++) {
        A[z] = mx;
        mx = max(mx, maxL[z]);
    }

    int mn = INF;
    for (int z = N; z >= 1; z--) {
        mn = min(mn, minL[z]);
        B[z] = mn;
    }

    // dp[z] = interval of possible previous 1 positions
    vector<int> lo(N + 2, INF);
    vector<int> hi(N + 2, -1);

    // All reachable positions z, in sorted order
    vector<int> w = {2};

    lo[2] = hi[2] = 1;

    for (int z = 3; z <= N; z++) {
        if (A[z] >= B[z]) continue;

        // Find first reachable i with hi[i] >= A[z]
        int l = 0, r = (int)w.size();

        while (l < r) {
            int mid = (l + r) / 2;

            if (hi[w[mid]] >= A[z])
                r = mid;
            else
                l = mid + 1;
        }

        int start = l;

        // Find first reachable i with lo[i] >= B[z]
        l = 0;
        r = (int)w.size();

        while (l < r) {
            int mid = (l + r) / 2;

            if (lo[w[mid]] >= B[z])
                r = mid;
            else
                l = mid + 1;
        }
        
        // ws swsfwi
        
        
        int end = l;

        if (start < end) {
            lo[z] = w[start];
            hi[z] = w[end - 1];
            w.push_back(z);
        }
    }
    // The last two sentinel positions must both be 1.
    cout << (lo[N] <= N - 1 && N - 1 <= hi[N]
                 ? "Yes" : "No") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) solve();

    return 0;
}

// wi dontw srnesst shso withsid ww