#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static const int MAXV = 1 << 20; 
            // 2^20 = 1,048,576, enough to cover any prefix‐XOR of up to 1e6.
static int freq[MAXV];

struct Query {
    int l, r, idx, block;
};
int BLOCK_SIZE;
bool mo_cmp(const Query &A, const Query &B) {
    if (A.block != B.block) 
        return A.block < B.block;
    // to reduce pointer‐jumps, alternate direction of R in odd/even blocks
    return (A.block & 1) ? (A.r > B.r) : (A.r < B.r);
}

vector<int> arr;
vector<int> pref;    // pref[0..n]: pref[i] = a[0]^a[1]^...^a[i-1]
ll currentAnswer = 0;
int k;

void add(int pos) {
    // including prefix index = pos (i.e. xor of first pos elements)
    int x = pref[pos];
    int want = x ^ k;
    // every existing prefix‐XOR == want forms a subarray‐xor == k
    currentAnswer += freq[want];
    freq[x]++;
}

void remove_(int pos) {
    // removing prefix index = pos
    int x = pref[pos];
    freq[x]--;
    int want = x ^ k;
    currentAnswer -= freq[want];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m >> k;

    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Build prefix‐XOR array of length (n+1):
    //   pref[0] = 0
    //   pref[i] = arr[0]^arr[1]^...^arr[i-1],  for i=1..n
    pref.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] ^ arr[i];
    }

    // Read queries and convert each [l, r] → prefix range [l-1, r]
    vector<Query> Q(m);
    BLOCK_SIZE = max(1, int(sqrt(n + 1)));
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;   // 1-based
        l--;             // now l ∈ [0..n-1]
        // We want the Mo-window to cover prefix indices [l .. r]:
        //   pref[l], pref[l+1], …, pref[r]
        Q[i].l = l;
        Q[i].r = r;
        Q[i].idx = i;
        Q[i].block = l / BLOCK_SIZE;
    }

    sort(Q.begin(), Q.end(), mo_cmp);

    vector<ll> answer(m);
    int currL = 0, currR = -1;
    currentAnswer = 0;
    memset(freq, 0, sizeof(freq));

    for (auto &q : Q) {
        int L = q.l, R = q.r;
        // Expand/shrink the window [currL..currR] → [L..R]

        while (currL > L) add(--currL);
        while (currR < R) add(++currR);
        while (currL < L) remove_(currL++);
        while (currR > R) remove_(currR--);

        answer[q.idx] = currentAnswer;
    }

    // Print in original input order
    for (int i = 0; i < m; i++) {
        cout << answer[i] << "\n";
    }
    return 0;
}
