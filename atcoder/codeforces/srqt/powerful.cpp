#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1e18;
const int MX = 1000001; // check the limits, dummy

// Modular arithmetic utilities
ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2);
        cur = (cur * cur) % MOD;
        if (power % 2 == 1) cur = (cur * base) % MOD;
        return cur;
    }
}

ll inv(ll base) {
    return modExp(base, MOD - 2);
}

ll mul(ll A, ll B) {
    return (A * B) % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

ll choose(ll a, ll b) {
    if (b > a || a < 0 || b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a - b]);
    return cur;
}

void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MX; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

// --------------------
// Mo's Algorithm setup
// --------------------

// A Query stores [l, r] (0-indexed) and its original index
struct Query {
    int l, r, idx, block;
};

// Comparator for sorting queries in Mo's order
bool mo_cmp(const Query& A, const Query& B) {
    if (A.block != B.block)
        return A.block < B.block;
    return (A.block & 1) ? (A.r > B.r) : (A.r < B.r);
}

// Global / static variables for Mo's
static int BLOCK_SIZE;
vector<ll> arr;
ll currentAnswer = 0;

// Example frequency array; adjust size if necessary
// If arr[i] can be up to 1e6, size it accordingly.
static const int MAXV = 1000001;
static int freq[MAXV];



void add(int pos) {
    ll x = arr[pos];
    ll prevcount = freq[x];

    currentAnswer -= (prevcount * prevcount) * x;

    freq[x] ++;
    ll newcount = freq[x];
    currentAnswer += (newcount * newcount) * x;

}

// Remove element at position pos from the current window
void remove_(int pos) {
    ll  x = arr[pos];
    ll  prevcount = freq[x];

    currentAnswer -= (prevcount * prevcount) * x;

    freq[x] --;
    
    ll newcount = freq[x];
    currentAnswer += (newcount * newcount) * x;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    initFacs(); // If you plan to use choose(), etc.
    int n, m, k;
    cin >> n >> m;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Build queries
    vector<Query> qs(m);
    BLOCK_SIZE = static_cast<int>(sqrt(n));
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        --l; --r; // convert to 0-based
        qs[i] = {l, r, i, l / BLOCK_SIZE};
    }

    sort(qs.begin(), qs.end(), mo_cmp);

    vector<ll> answers(m);
    int currL = 0, currR = -1;
    currentAnswer = 0;
    memset(freq, 0, sizeof(freq));

    for (auto& q : qs) {
        ll L = q.l;
        int R = q.r;
        while (currL > L) {
            add(--currL);
        }
        while (currR < R) {
            add(++currR);
        }
        while (currL < L) {
            remove_(currL++);
        }
        while (currR > R) {
            remove_(currR--);
        }
        answers[q.idx] = currentAnswer;
    }

    // Output answers in original order
    for (int i = 0; i < m; i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}
